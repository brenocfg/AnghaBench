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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_long ;
struct lpte {int /*<<< orphan*/  pte_lo; int /*<<< orphan*/  pte_hi; } ;
struct dump_context {int ptex; int blksz; int /*<<< orphan*/  ptex_end; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  H_READ ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phyp_pft_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
mphyp_dump_pmap(mmu_t mmu, void *ctx, void *buf, u_long *nbytes)
{
	struct dump_context *dctx;
	struct lpte p, *pbuf;
	int bufidx;
	uint64_t junk;
	u_long ptex, ptex_end;

	dctx = (struct dump_context *)ctx;
	pbuf = (struct lpte *)buf;
	bufidx = 0;
	ptex = dctx->ptex;
	ptex_end = ptex + dctx->blksz / sizeof(struct lpte);
	ptex_end = MIN(ptex_end, dctx->ptex_end);
	*nbytes = (ptex_end - ptex) * sizeof(struct lpte);

	if (*nbytes == 0)
		return (NULL);

	for (; ptex < ptex_end; ptex++) {
		phyp_pft_hcall(H_READ, 0, ptex, 0, 0,
			&p.pte_hi, &p.pte_lo, &junk);
		pbuf[bufidx++] = p;
	}

	dctx->ptex = ptex;
	return (buf);
}