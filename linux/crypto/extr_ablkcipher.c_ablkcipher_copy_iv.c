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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {unsigned int ivsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct ablkcipher_walk {unsigned int blocksize; int /*<<< orphan*/  iv; scalar_t__ iv_buffer; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned long,unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/ * ablkcipher_get_spot (int /*<<< orphan*/ *,unsigned int) ; 
 int crypto_tfm_ctx_alignment () ; 
 scalar_t__ kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int ablkcipher_copy_iv(struct ablkcipher_walk *walk,
				     struct crypto_tfm *tfm,
				     unsigned int alignmask)
{
	unsigned bs = walk->blocksize;
	unsigned int ivsize = tfm->crt_ablkcipher.ivsize;
	unsigned aligned_bs = ALIGN(bs, alignmask + 1);
	unsigned int size = aligned_bs * 2 + ivsize + max(aligned_bs, ivsize) -
			    (alignmask + 1);
	u8 *iv;

	size += alignmask & ~(crypto_tfm_ctx_alignment() - 1);
	walk->iv_buffer = kmalloc(size, GFP_ATOMIC);
	if (!walk->iv_buffer)
		return -ENOMEM;

	iv = (u8 *)ALIGN((unsigned long)walk->iv_buffer, alignmask + 1);
	iv = ablkcipher_get_spot(iv, bs) + aligned_bs;
	iv = ablkcipher_get_spot(iv, bs) + aligned_bs;
	iv = ablkcipher_get_spot(iv, ivsize);

	walk->iv = memcpy(iv, walk->iv, ivsize);
	return 0;
}