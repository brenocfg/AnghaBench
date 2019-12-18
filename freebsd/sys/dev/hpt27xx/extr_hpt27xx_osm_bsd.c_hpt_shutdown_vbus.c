#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* him_handle; } ;
struct TYPE_15__ {TYPE_2__ ldm_adapter; struct TYPE_15__* next; int /*<<< orphan*/  irq_handle; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  pcidev; } ;
struct TYPE_12__ {scalar_t__ ta_context; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; TYPE_4__* hba_list; TYPE_1__ worker; int /*<<< orphan*/  vbus; } ;
typedef  scalar_t__ PVDEV ;
typedef  TYPE_3__* PVBUS_EXT ;
typedef  int /*<<< orphan*/  PVBUS ;
typedef  TYPE_4__* PHBA ;

/* Variables and functions */
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hpt_flush_vdev (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  hpt_free_mem (TYPE_3__*) ; 
 int /*<<< orphan*/  hpt_lock_vbus (TYPE_3__*) ; 
 int /*<<< orphan*/  hpt_stop_tasks (TYPE_3__*) ; 
 int /*<<< orphan*/  hpt_unlock_vbus (TYPE_3__*) ; 
 scalar_t__ ldm_find_target (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldm_release_vbus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldm_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int osm_max_targets ; 

__attribute__((used)) static void hpt_shutdown_vbus(PVBUS_EXT vbus_ext, int howto)
{
	PVBUS     vbus = (PVBUS)vbus_ext->vbus;
	PHBA hba;
	int i;
	
	KdPrint(("hpt_shutdown_vbus"));

	/* stop all ctl tasks and disable the worker taskqueue */
	hpt_stop_tasks(vbus_ext);
	vbus_ext->worker.ta_context = 0;

	/* flush devices */
	for (i=0; i<osm_max_targets; i++) {
		PVDEV vd = ldm_find_target(vbus, i);
		if (vd) {
			/* retry once */
			if (hpt_flush_vdev(vbus_ext, vd))
				hpt_flush_vdev(vbus_ext, vd);
		}
	}

	hpt_lock_vbus(vbus_ext);
	ldm_shutdown(vbus);
	hpt_unlock_vbus(vbus_ext);

	ldm_release_vbus(vbus);

	for (hba=vbus_ext->hba_list; hba; hba=hba->next)
		bus_teardown_intr(hba->pcidev, hba->irq_res, hba->irq_handle);

	hpt_free_mem(vbus_ext);

	while ((hba=vbus_ext->hba_list)) {
		vbus_ext->hba_list = hba->next;
		free(hba->ldm_adapter.him_handle, M_DEVBUF);
	}
#if (__FreeBSD_version >= 1000510)
	callout_drain(&vbus_ext->timer);
	mtx_destroy(&vbus_ext->lock);
#endif
	free(vbus_ext, M_DEVBUF);
	KdPrint(("hpt_shutdown_vbus done"));
}