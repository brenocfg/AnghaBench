#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdma_controller_t ;
struct TYPE_3__ {int xr_num; int /*<<< orphan*/  bank; struct xdma_request* xr_mem; int /*<<< orphan*/ * xdma; } ;
typedef  TYPE_1__ xdma_channel_t ;
struct xdma_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  M_XDMA ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xdma_request*,int /*<<< orphan*/ ) ; 
 struct xdma_request* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xr_next ; 

void
xchan_bank_init(xdma_channel_t *xchan)
{
	struct xdma_request *xr;
	xdma_controller_t *xdma;
	int i;

	xdma = xchan->xdma;
	KASSERT(xdma != NULL, ("xdma is NULL"));

	xchan->xr_mem = malloc(sizeof(struct xdma_request) * xchan->xr_num,
	    M_XDMA, M_WAITOK | M_ZERO);

	for (i = 0; i < xchan->xr_num; i++) {
		xr = &xchan->xr_mem[i];
		TAILQ_INSERT_TAIL(&xchan->bank, xr, xr_next);
	}
}