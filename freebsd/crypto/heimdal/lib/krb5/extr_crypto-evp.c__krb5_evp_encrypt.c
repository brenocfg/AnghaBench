#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _krb5_key_data {TYPE_1__* schedule; } ;
struct _krb5_evp_schedule {int /*<<< orphan*/ * dctx; int /*<<< orphan*/ * ectx; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ krb5_boolean ;
struct TYPE_2__ {struct _krb5_evp_schedule* data; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 size_t EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,void*,void*,size_t) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

krb5_error_code
_krb5_evp_encrypt(krb5_context context,
		struct _krb5_key_data *key,
		void *data,
		size_t len,
		krb5_boolean encryptp,
		int usage,
		void *ivec)
{
    struct _krb5_evp_schedule *ctx = key->schedule->data;
    EVP_CIPHER_CTX *c;
    c = encryptp ? ctx->ectx : ctx->dctx;
    if (ivec == NULL) {
	/* alloca ? */
	size_t len2 = EVP_CIPHER_CTX_iv_length(c);
	void *loiv = malloc(len2);
	if (loiv == NULL) {
	    krb5_clear_error_message(context);
	    return ENOMEM;
	}
	memset(loiv, 0, len2);
	EVP_CipherInit_ex(c, NULL, NULL, NULL, loiv, -1);
	free(loiv);
    } else
	EVP_CipherInit_ex(c, NULL, NULL, NULL, ivec, -1);
    EVP_Cipher(c, data, data, len);
    return 0;
}