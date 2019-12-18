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
struct mfi_system_pd {int /*<<< orphan*/  pd_flags; TYPE_1__* pd_controller; int /*<<< orphan*/  pd_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mfi_io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MFI_DISK_FLAGS_DISABLED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mfi_syspd_enable(struct mfi_system_pd *sc)
{

	device_printf(sc->pd_dev, "syspd enable \n");
	mtx_assert(&sc->pd_controller->mfi_io_lock, MA_OWNED);
	sc->pd_flags &= ~MFI_DISK_FLAGS_DISABLED;
}