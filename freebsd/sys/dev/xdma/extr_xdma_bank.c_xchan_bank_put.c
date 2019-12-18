#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bank; } ;
typedef  TYPE_1__ xdma_channel_t ;
struct xdma_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_BANK_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  QUEUE_BANK_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xdma_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xr_next ; 

int
xchan_bank_put(xdma_channel_t *xchan, struct xdma_request *xr)
{

	QUEUE_BANK_LOCK(xchan);
	TAILQ_INSERT_TAIL(&xchan->bank, xr, xr_next);
	QUEUE_BANK_UNLOCK(xchan);

	return (0);
}