#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fkt_data {int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  TYPE_3__* krb5_principal ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_7__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_8__ {int /*<<< orphan*/  name_type; TYPE_1__ name_string; } ;
struct TYPE_9__ {TYPE_2__ name; int /*<<< orphan*/  realm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (TYPE_3__*,int) ; 
 int ENOMEM ; 
 int KRB5_KT_END ; 
 int /*<<< orphan*/  KRB5_NT_UNKNOWN ; 
 int /*<<< orphan*/  KRB5_STORAGE_PRINCIPAL_NO_NAME_TYPE ; 
 int /*<<< orphan*/  KRB5_STORAGE_PRINCIPAL_WRONG_NUM_COMPONENTS ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/ * calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int krb5_kt_ret_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int krb5_ret_int16 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int krb5_ret_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ krb5_storage_is_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
krb5_kt_ret_principal(krb5_context context,
		      struct fkt_data *fkt,
		      krb5_storage *sp,
		      krb5_principal *princ)
{
    size_t i;
    int ret;
    krb5_principal p;
    int16_t len;

    ALLOC(p, 1);
    if(p == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    ret = krb5_ret_int16(sp, &len);
    if(ret) {
	krb5_set_error_message(context, ret,
			       N_("Failed decoding length of "
				  "keytab principal in keytab file %s", ""),
			       fkt->filename);
	goto out;
    }
    if(krb5_storage_is_flags(sp, KRB5_STORAGE_PRINCIPAL_WRONG_NUM_COMPONENTS))
	len--;
    if (len < 0) {
	ret = KRB5_KT_END;
	krb5_set_error_message(context, ret,
			       N_("Keytab principal contains "
				  "invalid length in keytab %s", ""),
			       fkt->filename);
	goto out;
    }
    ret = krb5_kt_ret_string(context, sp, &p->realm);
    if(ret) {
	krb5_set_error_message(context, ret,
			       N_("Can't read realm from keytab: %s", ""),
			       fkt->filename);
	goto out;
    }
    p->name.name_string.val = calloc(len, sizeof(*p->name.name_string.val));
    if(p->name.name_string.val == NULL) {
	ret = ENOMEM;
	krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	goto out;
    }
    p->name.name_string.len = len;
    for(i = 0; i < p->name.name_string.len; i++){
	ret = krb5_kt_ret_string(context, sp, p->name.name_string.val + i);
	if(ret) {
	    krb5_set_error_message(context, ret,
				   N_("Can't read principal from "
				      "keytab: %s", ""),
				   fkt->filename);
	    goto out;
	}
    }
    if (krb5_storage_is_flags(sp, KRB5_STORAGE_PRINCIPAL_NO_NAME_TYPE))
	p->name.name_type = KRB5_NT_UNKNOWN;
    else {
	int32_t tmp32;
	ret = krb5_ret_int32(sp, &tmp32);
	p->name.name_type = tmp32;
	if (ret) {
	    krb5_set_error_message(context, ret,
				   N_("Can't read name-type from "
				      "keytab: %s", ""),
				   fkt->filename);
	    goto out;
	}
    }
    *princ = p;
    return 0;
out:
    krb5_free_principal(context, p);
    return ret;
}