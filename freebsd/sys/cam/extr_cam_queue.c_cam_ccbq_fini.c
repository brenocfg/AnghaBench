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
struct cam_ccbq {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  camq_fini (int /*<<< orphan*/ *) ; 

void
cam_ccbq_fini(struct cam_ccbq *ccbq)
{

	camq_fini(&ccbq->queue);
}