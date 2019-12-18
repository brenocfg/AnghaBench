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
struct mtk_ring {scalar_t__ cmd_next; scalar_t__ cmd_base; scalar_t__ res_base; scalar_t__ res_next; } ;
struct mtk_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ MTK_DESC_NUM ; 

__attribute__((used)) static inline void mtk_sha_ring_shift(struct mtk_ring *ring,
				      struct mtk_desc **cmd_curr,
				      struct mtk_desc **res_curr,
				      int *count)
{
	*cmd_curr = ring->cmd_next++;
	*res_curr = ring->res_next++;
	(*count)++;

	if (ring->cmd_next == ring->cmd_base + MTK_DESC_NUM) {
		ring->cmd_next = ring->cmd_base;
		ring->res_next = ring->res_base;
	}
}