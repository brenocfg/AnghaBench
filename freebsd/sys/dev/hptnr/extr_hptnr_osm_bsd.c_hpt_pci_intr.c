#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vbus; } ;
typedef  TYPE_1__* PVBUS_EXT ;
typedef  int /*<<< orphan*/  PVBUS ;

/* Variables and functions */
 int /*<<< orphan*/  hpt_lock_vbus (TYPE_1__*) ; 
 int /*<<< orphan*/  hpt_unlock_vbus (TYPE_1__*) ; 
 int /*<<< orphan*/  ldm_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpt_pci_intr(void *arg)
{	
	PVBUS_EXT vbus_ext = (PVBUS_EXT)arg;
	hpt_lock_vbus(vbus_ext);
	ldm_intr((PVBUS)vbus_ext->vbus);
	hpt_unlock_vbus(vbus_ext);
}