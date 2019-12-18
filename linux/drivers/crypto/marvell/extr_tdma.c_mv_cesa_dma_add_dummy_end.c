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
struct mv_cesa_tdma_desc {int /*<<< orphan*/  byte_cnt; } ;
struct mv_cesa_tdma_chain {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ IS_ERR (struct mv_cesa_tdma_desc*) ; 
 int PTR_ERR (struct mv_cesa_tdma_desc*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct mv_cesa_tdma_desc* mv_cesa_dma_add_desc (struct mv_cesa_tdma_chain*,int /*<<< orphan*/ ) ; 

int mv_cesa_dma_add_dummy_end(struct mv_cesa_tdma_chain *chain, gfp_t flags)
{
	struct mv_cesa_tdma_desc *tdma;

	tdma = mv_cesa_dma_add_desc(chain, flags);
	if (IS_ERR(tdma))
		return PTR_ERR(tdma);

	tdma->byte_cnt = cpu_to_le32(BIT(31));

	return 0;
}