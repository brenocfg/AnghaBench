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
struct mv_cesa_dma_iter {unsigned int len; scalar_t__ offset; int /*<<< orphan*/  op_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_SA_SRAM_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mv_cesa_req_dma_iter_init(struct mv_cesa_dma_iter *iter,
					     unsigned int len)
{
	iter->len = len;
	iter->op_len = min(len, CESA_SA_SRAM_PAYLOAD_SIZE);
	iter->offset = 0;
}