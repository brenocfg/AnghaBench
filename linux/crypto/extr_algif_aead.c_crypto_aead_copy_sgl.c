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
struct scatterlist {int dummy; } ;
struct crypto_sync_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  skreq ; 

__attribute__((used)) static int crypto_aead_copy_sgl(struct crypto_sync_skcipher *null_tfm,
				struct scatterlist *src,
				struct scatterlist *dst, unsigned int len)
{
	SYNC_SKCIPHER_REQUEST_ON_STACK(skreq, null_tfm);

	skcipher_request_set_sync_tfm(skreq, null_tfm);
	skcipher_request_set_callback(skreq, CRYPTO_TFM_REQ_MAY_BACKLOG,
				      NULL, NULL);
	skcipher_request_set_crypt(skreq, src, dst, len, NULL);

	return crypto_skcipher_encrypt(skreq);
}