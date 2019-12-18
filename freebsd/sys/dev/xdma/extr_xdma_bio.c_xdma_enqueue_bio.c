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
struct TYPE_6__ {int /*<<< orphan*/  queue_in; int /*<<< orphan*/ * xdma; } ;
typedef  TYPE_1__ xdma_channel_t ;
typedef  void* uint8_t ;
struct xdma_request {int direction; void* src_addr; void* dst_addr; void* dst_width; void* src_width; int /*<<< orphan*/  req_type; struct bio* bp; } ;
struct bio {int dummy; } ;
typedef  enum xdma_direction { ____Placeholder_xdma_direction } xdma_direction ;
typedef  void* bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_IN_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  QUEUE_IN_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xdma_request*,int /*<<< orphan*/ ) ; 
 int XDMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  XR_TYPE_BIO ; 
 struct xdma_request* xchan_bank_get (TYPE_1__*) ; 
 int /*<<< orphan*/  xr_next ; 

int
xdma_enqueue_bio(xdma_channel_t *xchan, struct bio **bp,
    bus_addr_t addr, uint8_t src_width, uint8_t dst_width,
    enum xdma_direction dir)
{
	struct xdma_request *xr;
	xdma_controller_t *xdma;

	xdma = xchan->xdma;

	xr = xchan_bank_get(xchan);
	if (xr == NULL)
		return (-1); /* No space is available yet. */

	xr->direction = dir;
	xr->bp = *bp;
	xr->req_type = XR_TYPE_BIO;
	xr->src_width = src_width;
	xr->dst_width = dst_width;
	if (dir == XDMA_MEM_TO_DEV) {
		xr->dst_addr = addr;
		xr->src_addr = 0;
	} else {
		xr->dst_addr = 0;
		xr->src_addr = addr;
	}

	QUEUE_IN_LOCK(xchan);
	TAILQ_INSERT_TAIL(&xchan->queue_in, xr, xr_next);
	QUEUE_IN_UNLOCK(xchan);

	return (0);
}