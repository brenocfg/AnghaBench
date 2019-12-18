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
struct crypto_skcipher {int dummy; } ;
struct crypto_cipher {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cia_decrypt; } ;

/* Variables and functions */
 TYPE_1__* crypto_cipher_alg (struct crypto_cipher*) ; 
 int crypto_ecb_crypt (struct skcipher_request*,struct crypto_cipher*,int /*<<< orphan*/ ) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct crypto_cipher* skcipher_cipher_simple (struct crypto_skcipher*) ; 

__attribute__((used)) static int crypto_ecb_decrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_cipher *cipher = skcipher_cipher_simple(tfm);

	return crypto_ecb_crypt(req, cipher,
				crypto_cipher_alg(cipher)->cia_decrypt);
}