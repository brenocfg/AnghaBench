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
typedef  int u_int32_t ;
struct ioat_softc {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
ioat_model_resets_msix(struct ioat_softc *ioat)
{
	u_int32_t pciid;

	pciid = pci_get_devid(ioat->device);
	switch (pciid) {
		/* BWD: */
	case 0x0c508086:
	case 0x0c518086:
	case 0x0c528086:
	case 0x0c538086:
		/* BDXDE: */
	case 0x6f508086:
	case 0x6f518086:
	case 0x6f528086:
	case 0x6f538086:
		return (TRUE);
	}

	return (FALSE);
}