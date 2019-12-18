#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  char uint16_t ;
typedef  int /*<<< orphan*/  ucs2 ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KRB5_PRINCIPAL_UNPARSE_NO_REALM ; 
 int /*<<< orphan*/  KRB5_STORAGE_BYTEORDER_LE ; 
 unsigned int WIND_RW_LE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_data_zero (int /*<<< orphan*/ *) ; 
 int krb5_enomem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int krb5_storage_to_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int krb5_storage_write (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  krb5_store_uint16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,int) ; 
 int krb5_unparse_name_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  out ; 
 int unix2nttime (int /*<<< orphan*/ ) ; 
 int wind_ucs2write (char*,size_t,unsigned int*,char*,size_t*) ; 
 int wind_utf8ucs2 (char*,char*,size_t*) ; 
 int wind_utf8ucs2_length (char*,size_t*) ; 

__attribute__((used)) static krb5_error_code
build_logon_name(krb5_context context,
		 time_t authtime,
		 krb5_const_principal principal,
		 krb5_data *logon)
{
    krb5_error_code ret;
    krb5_storage *sp;
    uint64_t t;
    char *s, *s2;
    size_t s2_len;

    t = unix2nttime(authtime);

    krb5_data_zero(logon);

    sp = krb5_storage_emem();
    if (sp == NULL)
	return krb5_enomem(context);

    krb5_storage_set_flags(sp, KRB5_STORAGE_BYTEORDER_LE);

    CHECK(ret, krb5_store_uint32(sp, t & 0xffffffff), out);
    CHECK(ret, krb5_store_uint32(sp, t >> 32), out);

    ret = krb5_unparse_name_flags(context, principal,
				  KRB5_PRINCIPAL_UNPARSE_NO_REALM, &s);
    if (ret)
	goto out;

    {
	size_t ucs2_len;
	uint16_t *ucs2;
	unsigned int flags;

	ret = wind_utf8ucs2_length(s, &ucs2_len);
	if (ret) {
	    free(s);
	    krb5_set_error_message(context, ret, "Failed to count length of UTF-8 string");
	    return ret;
	}

	ucs2 = malloc(sizeof(ucs2[0]) * ucs2_len);
	if (ucs2 == NULL) {
	    free(s);
	    return krb5_enomem(context);
	}

	ret = wind_utf8ucs2(s, ucs2, &ucs2_len);
	free(s);
	if (ret) {
	    free(ucs2);
	    krb5_set_error_message(context, ret, "Failed to convert string to UCS-2");
	    return ret;
	}

	s2_len = (ucs2_len + 1) * 2;
	s2 = malloc(s2_len);
	if (ucs2 == NULL) {
	    free(ucs2);
	    return krb5_enomem(context);
	}

	flags = WIND_RW_LE;
	ret = wind_ucs2write(ucs2, ucs2_len,
			     &flags, s2, &s2_len);
	free(ucs2);
	if (ret) {
	    free(s2);
	    krb5_set_error_message(context, ret, "Failed to write to UCS-2 buffer");
	    return ret;
	}

	/*
	 * we do not want zero termination
	 */
	s2_len = ucs2_len * 2;
    }

    CHECK(ret, krb5_store_uint16(sp, s2_len), out);

    ret = krb5_storage_write(sp, s2, s2_len);
    free(s2);
    if (ret != (int)s2_len) {
	ret = krb5_enomem(context);
	goto out;
    }
    ret = krb5_storage_to_data(sp, logon);
    if (ret)
	goto out;
    krb5_storage_free(sp);

    return 0;
out:
    krb5_storage_free(sp);
    return ret;
}