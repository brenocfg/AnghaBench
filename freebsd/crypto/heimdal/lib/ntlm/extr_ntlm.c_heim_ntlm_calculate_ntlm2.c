#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct ntlm_buf {unsigned char* data; int length; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;
struct TYPE_4__ {unsigned char* data; int length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  clientchallenge ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int HNTLM_ERR_RAND ; 
 int /*<<< orphan*/  KRB5_STORAGE_BYTEORDER_LE ; 
 int RAND_bytes (unsigned char*,int) ; 
 int heim_ntlm_derive_ntlm2_sess (unsigned char*,unsigned char*,int,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  heim_ntlm_ntlmv2_key (void const*,size_t,char const*,char const*,unsigned char*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_storage_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int unix2nttime (int /*<<< orphan*/ ) ; 

int
heim_ntlm_calculate_ntlm2(const void *key, size_t len,
			  const char *username,
			  const char *target,
			  const unsigned char serverchallenge[8],
			  const struct ntlm_buf *infotarget,
			  unsigned char ntlmv2[16],
			  struct ntlm_buf *answer)
{
    krb5_error_code ret;
    krb5_data data;
    unsigned char ntlmv2answer[16];
    krb5_storage *sp;
    unsigned char clientchallenge[8];
    uint64_t t;
    int code;

    t = unix2nttime(time(NULL));

    if (RAND_bytes(clientchallenge, sizeof(clientchallenge)) != 1)
	return HNTLM_ERR_RAND;

    /* calculate ntlmv2 key */

    heim_ntlm_ntlmv2_key(key, len, username, target, ntlmv2);

    /* calculate and build ntlmv2 answer */

    sp = krb5_storage_emem();
    if (sp == NULL)
	return ENOMEM;
    krb5_storage_set_flags(sp, KRB5_STORAGE_BYTEORDER_LE);

    CHECK(krb5_store_uint32(sp, 0x00000101), 0);
    CHECK(krb5_store_uint32(sp, 0), 0);
    /* timestamp le 64 bit ts */
    CHECK(krb5_store_uint32(sp, t & 0xffffffff), 0);
    CHECK(krb5_store_uint32(sp, t >> 32), 0);

    CHECK(krb5_storage_write(sp, clientchallenge, 8), 8);

    CHECK(krb5_store_uint32(sp, 0), 0);  /* unknown but zero will work */
    CHECK(krb5_storage_write(sp, infotarget->data, infotarget->length),
	  infotarget->length);
    CHECK(krb5_store_uint32(sp, 0), 0); /* unknown but zero will work */

    CHECK(krb5_storage_to_data(sp, &data), 0);
    krb5_storage_free(sp);
    sp = NULL;

    code = heim_ntlm_derive_ntlm2_sess(ntlmv2, data.data, data.length, serverchallenge, ntlmv2answer);
    if (code) {
	krb5_data_free(&data);
	return code;
    }

    sp = krb5_storage_emem();
    if (sp == NULL) {
	krb5_data_free(&data);
	return ENOMEM;
    }

    CHECK(krb5_storage_write(sp, ntlmv2answer, 16), 16);
    CHECK(krb5_storage_write(sp, data.data, data.length), data.length);
    krb5_data_free(&data);

    CHECK(krb5_storage_to_data(sp, &data), 0);
    krb5_storage_free(sp);
    sp = NULL;

    answer->data = data.data;
    answer->length = data.length;

    return 0;
out:
    if (sp)
	krb5_storage_free(sp);
    return ret;
}