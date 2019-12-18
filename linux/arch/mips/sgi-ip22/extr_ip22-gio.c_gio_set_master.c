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
typedef  int /*<<< orphan*/  u32 ;
struct gio_device {int slotno; } ;
struct TYPE_2__ {int /*<<< orphan*/  giopar; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGIMC_GIOPAR_MASTEREXP0 ; 
 int /*<<< orphan*/  SGIMC_GIOPAR_MASTEREXP1 ; 
 int /*<<< orphan*/  SGIMC_GIOPAR_MASTERGFX ; 
 TYPE_1__* sgimc ; 

void gio_set_master(struct gio_device *dev)
{
	u32 tmp = sgimc->giopar;

	switch (dev->slotno) {
	case 0:
		tmp |= SGIMC_GIOPAR_MASTERGFX;
		break;
	case 1:
		tmp |= SGIMC_GIOPAR_MASTEREXP0;
		break;
	case 2:
		tmp |= SGIMC_GIOPAR_MASTEREXP1;
		break;
	}
	sgimc->giopar = tmp;
}