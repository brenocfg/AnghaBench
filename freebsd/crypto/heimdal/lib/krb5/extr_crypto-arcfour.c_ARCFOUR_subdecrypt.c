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
typedef  int /*<<< orphan*/  t ;
struct _krb5_key_data {TYPE_2__* key; } ;
struct _krb5_checksum_type {int dummy; } ;
struct TYPE_5__ {int length; unsigned char* data; } ;
struct TYPE_6__ {TYPE_1__ keyvalue; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  k3_c_data ;
typedef  int /*<<< orphan*/  k2_c_data ;
typedef  int /*<<< orphan*/  k1_c_data ;
struct TYPE_7__ {TYPE_1__ checksum; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  TYPE_3__ Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  CKSUMTYPE_RSA_MD5 ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_rc4 () ; 
 scalar_t__ KRB5KRB_AP_ERR_BAD_INTEGRITY ; 
 struct _krb5_checksum_type* _krb5_find_checksum (int /*<<< orphan*/ ) ; 
 scalar_t__ _krb5_internal_hmac (int /*<<< orphan*/ *,struct _krb5_checksum_type*,unsigned char*,size_t,int /*<<< orphan*/ ,struct _krb5_key_data*,TYPE_3__*) ; 
 scalar_t__ ct_memcmp (unsigned char*,void*,int) ; 
 int /*<<< orphan*/  krb5_abortx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static krb5_error_code
ARCFOUR_subdecrypt(krb5_context context,
		   struct _krb5_key_data *key,
		   void *data,
		   size_t len,
		   unsigned usage,
		   void *ivec)
{
    EVP_CIPHER_CTX *ctx;
    struct _krb5_checksum_type *c = _krb5_find_checksum (CKSUMTYPE_RSA_MD5);
    Checksum k1_c, k2_c, k3_c, cksum;
    struct _krb5_key_data ke;
    krb5_keyblock kb;
    unsigned char t[4];
    unsigned char *cdata = data;
    unsigned char k1_c_data[16], k2_c_data[16], k3_c_data[16];
    unsigned char cksum_data[16];
    krb5_error_code ret;

    t[0] = (usage >>  0) & 0xFF;
    t[1] = (usage >>  8) & 0xFF;
    t[2] = (usage >> 16) & 0xFF;
    t[3] = (usage >> 24) & 0xFF;

    k1_c.checksum.length = sizeof(k1_c_data);
    k1_c.checksum.data   = k1_c_data;

    ret = _krb5_internal_hmac(NULL, c, t, sizeof(t), 0, key, &k1_c);
    if (ret)
	krb5_abortx(context, "hmac failed");

    memcpy (k2_c_data, k1_c_data, sizeof(k1_c_data));

    k2_c.checksum.length = sizeof(k2_c_data);
    k2_c.checksum.data   = k2_c_data;

    ke.key = &kb;
    kb.keyvalue = k1_c.checksum;

    k3_c.checksum.length = sizeof(k3_c_data);
    k3_c.checksum.data   = k3_c_data;

    ret = _krb5_internal_hmac(NULL, c, cdata, 16, 0, &ke, &k3_c);
    if (ret)
	krb5_abortx(context, "hmac failed");

    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL)
	krb5_abortx(context, "malloc failed");
    EVP_CipherInit_ex(ctx, EVP_rc4(), NULL, k3_c.checksum.data, NULL, 0);
    EVP_Cipher(ctx, cdata + 16, cdata + 16, len - 16);
    EVP_CIPHER_CTX_free(ctx);

    ke.key = &kb;
    kb.keyvalue = k2_c.checksum;

    cksum.checksum.length = 16;
    cksum.checksum.data   = cksum_data;

    ret = _krb5_internal_hmac(NULL, c, cdata + 16, len - 16, 0, &ke, &cksum);
    if (ret)
	krb5_abortx(context, "hmac failed");

    memset (k1_c_data, 0, sizeof(k1_c_data));
    memset (k2_c_data, 0, sizeof(k2_c_data));
    memset (k3_c_data, 0, sizeof(k3_c_data));

    if (ct_memcmp (cksum.checksum.data, data, 16) != 0) {
	krb5_clear_error_message (context);
	return KRB5KRB_AP_ERR_BAD_INTEGRITY;
    } else {
	return 0;
    }
}