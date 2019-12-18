#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  him_handle; TYPE_1__* him; } ;
struct TYPE_8__ {TYPE_4__ ldm_adapter; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_3__* hba_list; scalar_t__ vbus; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* initialize ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* PVBUS_EXT ;
typedef  int /*<<< orphan*/  PVBUS ;
typedef  TYPE_3__* PHBA ;

/* Variables and functions */
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  ldm_initialize_vbus (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpt_init_vbus(PVBUS_EXT vbus_ext)
{
	PHBA hba;

	for (hba = vbus_ext->hba_list; hba; hba = hba->next)
		if (!hba->ldm_adapter.him->initialize(hba->ldm_adapter.him_handle)) {
			KdPrint(("fail to initialize %p", hba));
			return -1;
		}

	ldm_initialize_vbus((PVBUS)vbus_ext->vbus, &vbus_ext->hba_list->ldm_adapter);
	return 0;
}