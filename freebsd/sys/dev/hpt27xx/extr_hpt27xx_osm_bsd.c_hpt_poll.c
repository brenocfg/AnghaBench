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
struct cam_sim {int dummy; } ;
struct TYPE_3__ {scalar_t__ vbus; } ;
typedef  TYPE_1__* PVBUS_EXT ;
typedef  int /*<<< orphan*/  PVBUS ;

/* Variables and functions */
 int /*<<< orphan*/  cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  hpt_assert_vbus_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  hpt_pci_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldm_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpt_poll(struct cam_sim *sim)
{
#if (__FreeBSD_version < 1000510)
	hpt_pci_intr(cam_sim_softc(sim));
#else 
	PVBUS_EXT vbus_ext = (PVBUS_EXT)cam_sim_softc(sim);

	hpt_assert_vbus_locked(vbus_ext);
	ldm_intr((PVBUS)vbus_ext->vbus);
#endif
}