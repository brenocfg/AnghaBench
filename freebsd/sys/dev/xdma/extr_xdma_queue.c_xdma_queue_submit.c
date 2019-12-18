#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdma_controller_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ * xdma; } ;
typedef  TYPE_1__ xdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XCHAN_LOCK (TYPE_1__*) ; 
 int XCHAN_TYPE_SG ; 
 int /*<<< orphan*/  XCHAN_UNLOCK (TYPE_1__*) ; 
 int xdma_queue_submit_sg (TYPE_1__*) ; 

int
xdma_queue_submit(xdma_channel_t *xchan)
{
	xdma_controller_t *xdma;
	int ret;

	xdma = xchan->xdma;
	KASSERT(xdma != NULL, ("xdma is NULL"));

	ret = 0;

	XCHAN_LOCK(xchan);

	if (xchan->flags & XCHAN_TYPE_SG)
		ret = xdma_queue_submit_sg(xchan);

	XCHAN_UNLOCK(xchan);

	return (ret);
}