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
typedef  scalar_t__ u32 ;
struct mv_cesa_tdma_desc {scalar_t__ flags; int /*<<< orphan*/  op; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  byte_cnt; struct mv_cesa_tdma_desc* next; } ;
struct mv_cesa_tdma_chain {struct mv_cesa_tdma_desc* first; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 scalar_t__ CESA_TDMA_DST_IN_SRAM ; 
 scalar_t__ CESA_TDMA_OP ; 
 scalar_t__ CESA_TDMA_RESULT ; 
 scalar_t__ CESA_TDMA_SRC_IN_SRAM ; 
 scalar_t__ CESA_TDMA_TYPE_MSK ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct mv_cesa_tdma_desc*) ; 
 int PTR_ERR (struct mv_cesa_tdma_desc*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 struct mv_cesa_tdma_desc* mv_cesa_dma_add_desc (struct mv_cesa_tdma_chain*,int /*<<< orphan*/ ) ; 

int mv_cesa_dma_add_result_op(struct mv_cesa_tdma_chain *chain, dma_addr_t src,
			  u32 size, u32 flags, gfp_t gfp_flags)
{
	struct mv_cesa_tdma_desc *tdma, *op_desc;

	tdma = mv_cesa_dma_add_desc(chain, gfp_flags);
	if (IS_ERR(tdma))
		return PTR_ERR(tdma);

	/* We re-use an existing op_desc object to retrieve the context
	 * and result instead of allocating a new one.
	 * There is at least one object of this type in a CESA crypto
	 * req, just pick the first one in the chain.
	 */
	for (op_desc = chain->first; op_desc; op_desc = op_desc->next) {
		u32 type = op_desc->flags & CESA_TDMA_TYPE_MSK;

		if (type == CESA_TDMA_OP)
			break;
	}

	if (!op_desc)
		return -EIO;

	tdma->byte_cnt = cpu_to_le32(size | BIT(31));
	tdma->src = src;
	tdma->dst = op_desc->src;
	tdma->op = op_desc->op;

	flags &= (CESA_TDMA_DST_IN_SRAM | CESA_TDMA_SRC_IN_SRAM);
	tdma->flags = flags | CESA_TDMA_RESULT;
	return 0;
}