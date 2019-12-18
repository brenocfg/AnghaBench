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
typedef  int /*<<< orphan*/  u64 ;
struct vmac_tfm_ctx {int /*<<< orphan*/ * l3key; int /*<<< orphan*/ * polykey; int /*<<< orphan*/  nhkey; } ;
struct vmac_desc_ctx {unsigned int partial_size; scalar_t__ first_block_processed; int /*<<< orphan*/  partial_words; int /*<<< orphan*/ * partial; int /*<<< orphan*/ * polytmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l3hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  m62 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nh_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poly_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int round_up (unsigned int,int) ; 

__attribute__((used)) static u64 vhash_final(const struct vmac_tfm_ctx *tctx,
		       struct vmac_desc_ctx *dctx)
{
	unsigned int partial = dctx->partial_size;
	u64 ch = dctx->polytmp[0];
	u64 cl = dctx->polytmp[1];

	/* L1 and L2-hash the final block if needed */
	if (partial) {
		/* Zero-pad to next 128-bit boundary */
		unsigned int n = round_up(partial, 16);
		u64 rh, rl;

		memset(&dctx->partial[partial], 0, n - partial);
		nh_16(dctx->partial_words, tctx->nhkey, n / 8, rh, rl);
		rh &= m62;
		if (dctx->first_block_processed)
			poly_step(ch, cl, tctx->polykey[0], tctx->polykey[1],
				  rh, rl);
		else
			ADD128(ch, cl, rh, rl);
	}

	/* L3-hash the 128-bit output of L2-hash */
	return l3hash(ch, cl, tctx->l3key[0], tctx->l3key[1], partial * 8);
}