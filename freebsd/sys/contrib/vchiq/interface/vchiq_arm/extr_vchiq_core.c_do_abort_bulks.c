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
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_5__ {int /*<<< orphan*/  bulk_rx; int /*<<< orphan*/  bulk_tx; int /*<<< orphan*/  bulk_mutex; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  abort_outstanding_bulks (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lmutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ notify_bulks (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_abort_bulks(VCHIQ_SERVICE_T *service)
{
	VCHIQ_STATUS_T status;

	/* Abort any outstanding bulk transfers */
	if (lmutex_lock_interruptible(&service->bulk_mutex) != 0)
		return 0;
	abort_outstanding_bulks(service, &service->bulk_tx);
	abort_outstanding_bulks(service, &service->bulk_rx);
	lmutex_unlock(&service->bulk_mutex);

	status = notify_bulks(service, &service->bulk_tx, 0/*!retry_poll*/);
	if (status == VCHIQ_SUCCESS)
		status = notify_bulks(service, &service->bulk_rx,
			0/*!retry_poll*/);
	return (status == VCHIQ_SUCCESS);
}