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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct crypto_sync_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int crypto_skcipher_decrypt (int /*<<< orphan*/ ) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreq ; 

__attribute__((used)) static int chcr_cipher_fallback(struct crypto_sync_skcipher *cipher,
				u32 flags,
				struct scatterlist *src,
				struct scatterlist *dst,
				unsigned int nbytes,
				u8 *iv,
				unsigned short op_type)
{
	int err;

	SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, cipher);

	skcipher_request_set_sync_tfm(subreq, cipher);
	skcipher_request_set_callback(subreq, flags, NULL, NULL);
	skcipher_request_set_crypt(subreq, src, dst,
				   nbytes, iv);

	err = op_type ? crypto_skcipher_decrypt(subreq) :
		crypto_skcipher_encrypt(subreq);
	skcipher_request_zero(subreq);

	return err;

}