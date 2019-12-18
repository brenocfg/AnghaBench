#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ addr; } ;
struct TYPE_5__ {TYPE_4__ virt; } ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct TYPE_7__ {TYPE_2__ virt; } ;
struct skcipher_walk {unsigned int nbytes; TYPE_1__ dst; TYPE_3__ src; } ;
struct skcipher_request {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 unsigned int crypto_pcbc_decrypt_inplace (struct skcipher_request*,struct skcipher_walk*,struct crypto_cipher*) ; 
 unsigned int crypto_pcbc_decrypt_segment (struct skcipher_request*,struct skcipher_walk*,struct crypto_cipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct crypto_cipher* skcipher_cipher_simple (struct crypto_skcipher*) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int crypto_pcbc_decrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	struct skcipher_walk walk;
	unsigned int nbytes;
	int err;

	err = skcipher_walk_virt(&walk, req, false);

	while ((nbytes = walk.nbytes)) {
		if (walk.src.virt.addr == walk.dst.virt.addr)
			nbytes = crypto_pcbc_decrypt_inplace(req, &walk,
							     cipher);
		else
			nbytes = crypto_pcbc_decrypt_segment(req, &walk,
							     cipher);
		err = skcipher_walk_done(&walk, nbytes);
	}

	return err;
}