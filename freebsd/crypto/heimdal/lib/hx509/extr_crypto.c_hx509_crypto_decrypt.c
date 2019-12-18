#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* hx509_crypto ;
struct TYPE_11__ {unsigned char* data; size_t length; } ;
typedef  TYPE_4__ heim_octet_string ;
struct TYPE_9__ {int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  c; TYPE_2__ key; TYPE_1__* cipher; } ;
struct TYPE_8__ {int flags; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int ALLOW_WEAK ; 
 int CIPHER_WEAK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int EVP_CIPHER_block_size (int /*<<< orphan*/ ) ; 
 int EVP_CIPHER_iv_length (int /*<<< orphan*/ ) ; 
 int EVP_Cipher (int /*<<< orphan*/ *,unsigned char*,void const*,size_t const) ; 
 int EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int HX509_CMS_PADDING_ERROR ; 
 int HX509_CRYPTO_ALGORITHM_BEST_BEFORE ; 
 int HX509_CRYPTO_INTERNAL_ERROR ; 
 int PADDING_PKCS7 ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (size_t const) ; 

int
hx509_crypto_decrypt(hx509_crypto crypto,
		     const void *data,
		     const size_t length,
		     heim_octet_string *ivec,
		     heim_octet_string *clear)
{
    EVP_CIPHER_CTX *evp;
    void *idata = NULL;
    int ret;

    clear->data = NULL;
    clear->length = 0;

    if ((crypto->cipher->flags & CIPHER_WEAK) &&
	(crypto->flags & ALLOW_WEAK) == 0)
	return HX509_CRYPTO_ALGORITHM_BEST_BEFORE;

    if (ivec && EVP_CIPHER_iv_length(crypto->c) < (int)ivec->length)
	return HX509_CRYPTO_INTERNAL_ERROR;

    if (crypto->key.data == NULL)
	return HX509_CRYPTO_INTERNAL_ERROR;

    if (ivec)
	idata = ivec->data;

    evp = EVP_CIPHER_CTX_new();
    if (evp == NULL)
	return ENOMEM;

    ret = EVP_CipherInit_ex(evp, crypto->c, NULL,
			    crypto->key.data, idata, 0);
    if (ret != 1) {
	EVP_CIPHER_CTX_free(evp);
	return HX509_CRYPTO_INTERNAL_ERROR;
    }

    clear->length = length;
    clear->data = malloc(length);
    if (clear->data == NULL) {
	EVP_CIPHER_CTX_free(evp);
	clear->length = 0;
	return ENOMEM;
    }

    if (EVP_Cipher(evp, clear->data, data, length) != 1) {
	EVP_CIPHER_CTX_free(evp);
	return HX509_CRYPTO_INTERNAL_ERROR;
    }
    EVP_CIPHER_CTX_free(evp);

    if ((crypto->flags & PADDING_PKCS7) && EVP_CIPHER_block_size(crypto->c) > 1) {
	int padsize;
	unsigned char *p;
	int j, bsize = EVP_CIPHER_block_size(crypto->c);

	if ((int)clear->length < bsize) {
	    ret = HX509_CMS_PADDING_ERROR;
	    goto out;
	}

	p = clear->data;
	p += clear->length - 1;
	padsize = *p;
	if (padsize > bsize) {
	    ret = HX509_CMS_PADDING_ERROR;
	    goto out;
	}
	clear->length -= padsize;
	for (j = 0; j < padsize; j++) {
	    if (*p-- != padsize) {
		ret = HX509_CMS_PADDING_ERROR;
		goto out;
	    }
	}
    }

    return 0;

 out:
    if (clear->data)
	free(clear->data);
    clear->data = NULL;
    clear->length = 0;
    return ret;
}