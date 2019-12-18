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
struct xdma_request {int direction; int block_num; uintptr_t src_addr; uintptr_t dst_addr; void* dst_width; void* src_width; int /*<<< orphan*/  req_type; int /*<<< orphan*/  block_len; int /*<<< orphan*/ * bp; int /*<<< orphan*/ * m; void* user; } ;
typedef  enum xdma_direction { ____Placeholder_xdma_direction } xdma_direction ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QUEUE_IN_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  QUEUE_IN_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xdma_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XR_TYPE_VIRT ; 
 struct xdma_request* xchan_bank_get (TYPE_1__*) ; 
 int /*<<< orphan*/  xr_next ; 

int
xdma_enqueue(xdma_channel_t *xchan, uintptr_t src, uintptr_t dst,
    uint8_t src_width, uint8_t dst_width, bus_size_t len,
    enum xdma_direction dir, void *user)
{
	struct xdma_request *xr;
	xdma_controller_t *xdma;

	xdma = xchan->xdma;
	KASSERT(xdma != NULL, ("xdma is NULL"));

	xr = xchan_bank_get(xchan);
	if (xr == NULL)
		return (-1); /* No space is available. */

	xr->user = user;
	xr->direction = dir;
	xr->m = NULL;
	xr->bp = NULL;
	xr->block_num = 1;
	xr->block_len = len;
	xr->req_type = XR_TYPE_VIRT;
	xr->src_addr = src;
	xr->dst_addr = dst;
	xr->src_width = src_width;
	xr->dst_width = dst_width;

	QUEUE_IN_LOCK(xchan);
	TAILQ_INSERT_TAIL(&xchan->queue_in, xr, xr_next);
	QUEUE_IN_UNLOCK(xchan);

	return (0);
}