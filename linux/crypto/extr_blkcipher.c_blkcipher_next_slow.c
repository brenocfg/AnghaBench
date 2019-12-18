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
struct TYPE_7__ {void* addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; int /*<<< orphan*/  flags; int /*<<< orphan*/  in; TYPE_4__ src; TYPE_2__ dst; scalar_t__ buffer; scalar_t__ page; } ;
struct blkcipher_desc {int dummy; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  BLKCIPHER_WALK_SLOW ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* blkcipher_get_spot (int /*<<< orphan*/ *,unsigned int) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,int /*<<< orphan*/ ) ; 
 int crypto_tfm_ctx_alignment () ; 
 scalar_t__ kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (void*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int blkcipher_next_slow(struct blkcipher_desc *desc,
				      struct blkcipher_walk *walk,
				      unsigned int bsize,
				      unsigned int alignmask)
{
	unsigned int n;
	unsigned aligned_bsize = ALIGN(bsize, alignmask + 1);

	if (walk->buffer)
		goto ok;

	walk->buffer = walk->page;
	if (walk->buffer)
		goto ok;

	n = aligned_bsize * 3 - (alignmask + 1) +
	    (alignmask & ~(crypto_tfm_ctx_alignment() - 1));
	walk->buffer = kmalloc(n, GFP_ATOMIC);
	if (!walk->buffer)
		return blkcipher_walk_done(desc, walk, -ENOMEM);

ok:
	walk->dst.virt.addr = (u8 *)ALIGN((unsigned long)walk->buffer,
					  alignmask + 1);
	walk->dst.virt.addr = blkcipher_get_spot(walk->dst.virt.addr, bsize);
	walk->src.virt.addr = blkcipher_get_spot(walk->dst.virt.addr +
						 aligned_bsize, bsize);

	scatterwalk_copychunks(walk->src.virt.addr, &walk->in, bsize, 0);

	walk->nbytes = bsize;
	walk->flags |= BLKCIPHER_WALK_SLOW;

	return 0;
}