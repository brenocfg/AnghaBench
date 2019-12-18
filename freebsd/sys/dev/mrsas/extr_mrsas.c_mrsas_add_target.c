#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int16_t ;
struct mrsas_softc {scalar_t__ pd_info_mem; int /*<<< orphan*/  mask_interrupts; int /*<<< orphan*/  mrsas_dev; TYPE_1__* target_list; } ;
struct TYPE_2__ {size_t target_id; } ;

/* Variables and functions */
 size_t MRSAS_MAX_PD ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,size_t) ; 
 int /*<<< orphan*/  mrsas_get_pd_info (struct mrsas_softc*,size_t) ; 

__attribute__((used)) static void mrsas_add_target(struct mrsas_softc *sc,
	u_int16_t target_id)
{
	sc->target_list[target_id].target_id = target_id;

	device_printf(sc->mrsas_dev,
		"%s created target ID: 0x%x\n",
		(target_id < MRSAS_MAX_PD ? "System PD" : "VD"),
		(target_id < MRSAS_MAX_PD ? target_id : (target_id - MRSAS_MAX_PD)));
	/*
	 * If interrupts are enabled, then only fire DCMD to get pd_info
	 * for system PDs
	 */
	if (!sc->mask_interrupts && sc->pd_info_mem &&
		(target_id < MRSAS_MAX_PD))
		mrsas_get_pd_info(sc, target_id);

}