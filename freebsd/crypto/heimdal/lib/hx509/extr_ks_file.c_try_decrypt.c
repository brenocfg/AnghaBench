#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hx509_collector {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_3__ {void* data; size_t length; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int ENOMEM ; 
 int EVP_BytesToKey (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void const*,void const*,size_t,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 size_t EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,void*,void const*,size_t) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int HX509_CRYPTO_INTERNAL_ERROR ; 
 int _hx509_collector_private_key_add (int /*<<< orphan*/ ,struct hx509_collector*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
try_decrypt(hx509_context context,
	    struct hx509_collector *collector,
	    const AlgorithmIdentifier *alg,
	    const EVP_CIPHER *c,
	    const void *ivdata,
	    const void *password,
	    size_t passwordlen,
	    const void *cipher,
	    size_t len)
{
    heim_octet_string clear;
    size_t keylen;
    void *key;
    int ret;

    keylen = EVP_CIPHER_key_length(c);

    key = malloc(keylen);
    if (key == NULL) {
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    ret = EVP_BytesToKey(c, EVP_md5(), ivdata,
			 password, passwordlen,
			 1, key, NULL);
    if (ret <= 0) {
	hx509_set_error_string(context, 0, HX509_CRYPTO_INTERNAL_ERROR,
			       "Failed to do string2key for private key");
	return HX509_CRYPTO_INTERNAL_ERROR;
    }

    clear.data = malloc(len);
    if (clear.data == NULL) {
	hx509_set_error_string(context, 0, ENOMEM,
			       "Out of memory to decrypt for private key");
	ret = ENOMEM;
	goto out;
    }
    clear.length = len;

    {
	EVP_CIPHER_CTX *ctx;

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL) {
		hx509_set_error_string(context, 0, ENOMEM,
				       "Out of memory to decrypt for private key");
		ret = ENOMEM;
		goto out;
	}
	EVP_CipherInit_ex(ctx, c, NULL, key, ivdata, 0);
	EVP_Cipher(ctx, clear.data, cipher, len);
	EVP_CIPHER_CTX_free(ctx);
    }

    ret = _hx509_collector_private_key_add(context,
					   collector,
					   alg,
					   NULL,
					   &clear,
					   NULL);

    memset(clear.data, 0, clear.length);
out:
    free(clear.data);
    memset(key, 0, keylen);
    free(key);
    return ret;
}