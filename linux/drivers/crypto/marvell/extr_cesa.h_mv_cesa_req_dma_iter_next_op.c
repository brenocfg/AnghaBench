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
struct mv_cesa_dma_iter {int offset; int op_len; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_SA_SRAM_PAYLOAD_SIZE ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool mv_cesa_req_dma_iter_next_op(struct mv_cesa_dma_iter *iter)
{
	iter->offset += iter->op_len;
	iter->op_len = min(iter->len - iter->offset,
			   CESA_SA_SRAM_PAYLOAD_SIZE);

	return iter->op_len;
}