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
struct t4_cq {int sw_in_use; scalar_t__ sw_cidx; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void t4_swcq_consume(struct t4_cq *cq)
{
	assert(cq->sw_in_use >= 1);
	cq->sw_in_use--;
	if (++cq->sw_cidx == cq->size)
		cq->sw_cidx = 0;
}