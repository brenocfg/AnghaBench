#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_4__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; int /*<<< orphan*/ * iv; TYPE_2__ src; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int MAX_CIPHER_BLOCKSIZE ; 
 unsigned int crypto_cfb_bsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_cfb_encrypt_one (struct crypto_skcipher*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int const) ; 

__attribute__((used)) static int crypto_cfb_encrypt_inplace(struct skcipher_walk *walk,
				      struct crypto_skcipher *tfm)
{
	const unsigned int bsize = crypto_cfb_bsize(tfm);
	unsigned int nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 *iv = walk->iv;
	u8 tmp[MAX_CIPHER_BLOCKSIZE];

	do {
		crypto_cfb_encrypt_one(tfm, iv, tmp);
		crypto_xor(src, tmp, bsize);
		iv = src;

		src += bsize;
	} while ((nbytes -= bsize) >= bsize);

	memcpy(walk->iv, iv, bsize);

	return nbytes;
}