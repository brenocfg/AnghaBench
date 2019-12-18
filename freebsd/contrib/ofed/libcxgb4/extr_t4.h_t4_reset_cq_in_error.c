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
struct t4_status_page {scalar_t__ qp_err; } ;
struct t4_cq {size_t size; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */

__attribute__((used)) static inline void t4_reset_cq_in_error(struct t4_cq *cq)
{
	((struct t4_status_page *)&cq->queue[cq->size])->qp_err = 0;
}