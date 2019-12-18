#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct agp_amd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_AMD751_TLBCTRL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ READ4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (int /*<<< orphan*/ ,int) ; 
 struct agp_amd_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
agp_amd_flush_tlb(device_t dev)
{
	struct agp_amd_softc *sc = device_get_softc(dev);

	/* Set the cache invalidate bit and wait for the chipset to clear */
	WRITE4(AGP_AMD751_TLBCTRL, 1);
	do {
		DELAY(1);
	} while (READ4(AGP_AMD751_TLBCTRL));
}