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
struct cmpl_base {int info3_v; } ;
struct TYPE_2__ {int ring_size; scalar_t__ vaddr; } ;
struct bnxt_cp_ring {int /*<<< orphan*/  v_bit; TYPE_1__ ring; } ;

/* Variables and functions */

__attribute__((used)) static void
bnxt_mark_cpr_invalid(struct bnxt_cp_ring *cpr)
{
	struct cmpl_base *cmp = (void *)cpr->ring.vaddr;
	int i;

	for (i = 0; i < cpr->ring.ring_size; i++)
		cmp[i].info3_v = !cpr->v_bit;
}