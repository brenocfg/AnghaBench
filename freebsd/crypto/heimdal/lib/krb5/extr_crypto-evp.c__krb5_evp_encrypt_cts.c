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
 int /*<<< orphan*/  EINVAL ; 
 size_t EVP_CIPHER_CTX_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 int EVP_MAX_BLOCK_LENGTH ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 
 void* zero_ivec ; 

krb5_error_code
_krb5_evp_encrypt_cts(krb5_context context,
		      struct _krb5_key_data *key,
		      void *data,
		      size_t len,
		      krb5_boolean encryptp,
		      int usage,
		      void *ivec)
{
    size_t i, blocksize;
    struct _krb5_evp_schedule *ctx = key->schedule->data;
    unsigned char tmp[EVP_MAX_BLOCK_LENGTH], ivec2[EVP_MAX_BLOCK_LENGTH];
    EVP_CIPHER_CTX *c;
    unsigned char *p;

    c = encryptp ? ctx->ectx : ctx->dctx;

    blocksize = EVP_CIPHER_CTX_block_size(c);

    if (len < blocksize) {
	krb5_set_error_message(context, EINVAL,
			       "message block too short");
	return EINVAL;
    } else if (len == blocksize) {
	EVP_CipherInit_ex(c, NULL, NULL, NULL, zero_ivec, -1);
	EVP_Cipher(c, data, data, len);
	return 0;
    }

    if (ivec)
	EVP_CipherInit_ex(c, NULL, NULL, NULL, ivec, -1);
    else
	EVP_CipherInit_ex(c, NULL, NULL, NULL, zero_ivec, -1);

    if (encryptp) {

	p = data;
	i = ((len - 1) / blocksize) * blocksize;
	EVP_Cipher(c, p, p, i);
	p += i - blocksize;
	len -= i;
	memcpy(ivec2, p, blocksize);

	for (i = 0; i < len; i++)
	    tmp[i] = p[i + blocksize] ^ ivec2[i];
	for (; i < blocksize; i++)
	    tmp[i] = 0 ^ ivec2[i];

	EVP_CipherInit_ex(c, NULL, NULL, NULL, zero_ivec, -1);
	EVP_Cipher(c, p, tmp, blocksize);

	memcpy(p + blocksize, ivec2, len);
	if (ivec)
	    memcpy(ivec, p, blocksize);
    } else {
	unsigned char tmp2[EVP_MAX_BLOCK_LENGTH], tmp3[EVP_MAX_BLOCK_LENGTH];

	p = data;
	if (len > blocksize * 2) {
	    /* remove last two blocks and round up, decrypt this with cbc, then do cts dance */
	    i = ((((len - blocksize * 2) + blocksize - 1) / blocksize) * blocksize);
	    memcpy(ivec2, p + i - blocksize, blocksize);
	    EVP_Cipher(c, p, p, i);
	    p += i;
	    len -= i + blocksize;
	} else {
	    if (ivec)
		memcpy(ivec2, ivec, blocksize);
	    else
		memcpy(ivec2, zero_ivec, blocksize);
	    len -= blocksize;
	}

	memcpy(tmp, p, blocksize);
	EVP_CipherInit_ex(c, NULL, NULL, NULL, zero_ivec, -1);
	EVP_Cipher(c, tmp2, p, blocksize);

	memcpy(tmp3, p + blocksize, len);
	memcpy(tmp3 + len, tmp2 + len, blocksize - len); /* xor 0 */

	for (i = 0; i < len; i++)
	    p[i + blocksize] = tmp2[i] ^ tmp3[i];

	EVP_CipherInit_ex(c, NULL, NULL, NULL, zero_ivec, -1);
	EVP_Cipher(c, p, tmp3, blocksize);

	for (i = 0; i < blocksize; i++)
	    p[i] ^= ivec2[i];
	if (ivec)
	    memcpy(ivec, tmp, blocksize);
    }
    return 0;
}