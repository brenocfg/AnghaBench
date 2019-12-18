#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ ** services; } ;
typedef  TYPE_2__ VCHIQ_STATE_T ;
struct TYPE_6__ {int /*<<< orphan*/  userdata; } ;
struct TYPE_8__ {scalar_t__ ref_count; scalar_t__ srvstate; size_t localport; TYPE_1__ base; int /*<<< orphan*/  (* userdata_term ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  bulk_mutex; int /*<<< orphan*/  bulk_remove_event; int /*<<< orphan*/  remove_event; TYPE_2__* state; } ;
typedef  TYPE_3__ VCHIQ_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ VCHIQ_SRVSTATE_FREE ; 
 int /*<<< orphan*/  _sema_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  lmutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_spinlock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
unlock_service(VCHIQ_SERVICE_T *service)
{
	VCHIQ_STATE_T *state = service->state;
	spin_lock(&service_spinlock);
	BUG_ON(!service || (service->ref_count == 0));
	if (service && service->ref_count) {
		service->ref_count--;
		if (!service->ref_count) {
			BUG_ON(service->srvstate != VCHIQ_SRVSTATE_FREE);
			state->services[service->localport] = NULL;

			_sema_destroy(&service->remove_event);
			_sema_destroy(&service->bulk_remove_event);
			lmutex_destroy(&service->bulk_mutex);
		} else
			service = NULL;
	}
	spin_unlock(&service_spinlock);

	if (service && service->userdata_term)
		service->userdata_term(service->base.userdata);

	kfree(service);
}