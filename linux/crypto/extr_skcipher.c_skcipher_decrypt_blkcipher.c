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
struct skcipher_request {int dummy; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct crypto_skcipher {int dummy; } ;
struct blkcipher_alg {int /*<<< orphan*/  decrypt; } ;
struct TYPE_2__ {struct blkcipher_alg cra_blkcipher; } ;

/* Variables and functions */
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 int skcipher_crypt_blkcipher (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skcipher_decrypt_blkcipher(struct skcipher_request *req)
{
	struct crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	struct crypto_tfm *tfm = crypto_skcipher_tfm(skcipher);
	struct blkcipher_alg *alg = &tfm->__crt_alg->cra_blkcipher;

	return skcipher_crypt_blkcipher(req, alg->decrypt);
}