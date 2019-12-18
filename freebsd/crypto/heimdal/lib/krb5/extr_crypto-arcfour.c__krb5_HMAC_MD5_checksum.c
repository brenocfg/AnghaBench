#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct _krb5_key_data {TYPE_2__* key; } ;
struct _krb5_checksum_type {int dummy; } ;
typedef  int /*<<< orphan*/  signature ;
typedef  int /*<<< orphan*/  ksign_c_data ;
struct TYPE_5__ {int length; unsigned char* data; } ;
struct TYPE_6__ {TYPE_1__ keyvalue; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_7__ {TYPE_1__ checksum; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_3__ Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  CKSUMTYPE_RSA_MD5 ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 struct _krb5_checksum_type* _krb5_find_checksum (int /*<<< orphan*/ ) ; 
 scalar_t__ _krb5_internal_hmac (int /*<<< orphan*/ ,struct _krb5_checksum_type*,...) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

krb5_error_code
_krb5_HMAC_MD5_checksum(krb5_context context,
			struct _krb5_key_data *key,
			const void *data,
			size_t len,
			unsigned usage,
			Checksum *result)
{
    EVP_MD_CTX *m;
    struct _krb5_checksum_type *c = _krb5_find_checksum (CKSUMTYPE_RSA_MD5);
    const char signature[] = "signaturekey";
    Checksum ksign_c;
    struct _krb5_key_data ksign;
    krb5_keyblock kb;
    unsigned char t[4];
    unsigned char tmp[16];
    unsigned char ksign_c_data[16];
    krb5_error_code ret;

    m = EVP_MD_CTX_create();
    if (m == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    ksign_c.checksum.length = sizeof(ksign_c_data);
    ksign_c.checksum.data   = ksign_c_data;
    ret = _krb5_internal_hmac(context, c, signature, sizeof(signature),
			      0, key, &ksign_c);
    if (ret) {
	EVP_MD_CTX_destroy(m);
	return ret;
    }
    ksign.key = &kb;
    kb.keyvalue = ksign_c.checksum;
    EVP_DigestInit_ex(m, EVP_md5(), NULL);
    t[0] = (usage >>  0) & 0xFF;
    t[1] = (usage >>  8) & 0xFF;
    t[2] = (usage >> 16) & 0xFF;
    t[3] = (usage >> 24) & 0xFF;
    EVP_DigestUpdate(m, t, 4);
    EVP_DigestUpdate(m, data, len);
    EVP_DigestFinal_ex (m, tmp, NULL);
    EVP_MD_CTX_destroy(m);

    ret = _krb5_internal_hmac(context, c, tmp, sizeof(tmp), 0, &ksign, result);
    if (ret)
	return ret;
    return 0;
}