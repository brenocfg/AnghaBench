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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {int nbytes; scalar_t__ total; int /*<<< orphan*/ * iv; TYPE_4__ src; TYPE_2__ dst; } ;
struct crypto_aes_ctx {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_xor_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int skcipher_walk_done (struct skcipher_walk*,scalar_t__) ; 

__attribute__((used)) static int ccm_crypt_fallback(struct skcipher_walk *walk, u8 mac[], u8 iv0[],
			      struct crypto_aes_ctx *ctx, bool enc)
{
	u8 buf[AES_BLOCK_SIZE];
	int err = 0;

	while (walk->nbytes) {
		int blocks = walk->nbytes / AES_BLOCK_SIZE;
		u32 tail = walk->nbytes % AES_BLOCK_SIZE;
		u8 *dst = walk->dst.virt.addr;
		u8 *src = walk->src.virt.addr;
		u32 nbytes = walk->nbytes;

		if (nbytes == walk->total && tail > 0) {
			blocks++;
			tail = 0;
		}

		do {
			u32 bsize = AES_BLOCK_SIZE;

			if (nbytes < AES_BLOCK_SIZE)
				bsize = nbytes;

			crypto_inc(walk->iv, AES_BLOCK_SIZE);
			aes_encrypt(ctx, buf, walk->iv);
			aes_encrypt(ctx, mac, mac);
			if (enc)
				crypto_xor(mac, src, bsize);
			crypto_xor_cpy(dst, src, buf, bsize);
			if (!enc)
				crypto_xor(mac, dst, bsize);
			dst += bsize;
			src += bsize;
			nbytes -= bsize;
		} while (--blocks);

		err = skcipher_walk_done(walk, tail);
	}

	if (!err) {
		aes_encrypt(ctx, buf, iv0);
		aes_encrypt(ctx, mac, mac);
		crypto_xor(mac, buf, AES_BLOCK_SIZE);
	}
	return err;
}