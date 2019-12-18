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
struct oce_wq {TYPE_1__* cq; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  oce_arm_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
oce_start_wq(struct oce_wq *wq)
{
	oce_arm_cq(wq->parent, wq->cq->cq_id, 0, TRUE);
	return 0;
}