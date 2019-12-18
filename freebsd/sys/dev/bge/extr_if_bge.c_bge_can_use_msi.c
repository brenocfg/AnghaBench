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
struct bge_softc {scalar_t__ bge_msi; int bge_asicrev; int /*<<< orphan*/  bge_chiprev; } ;

/* Variables and functions */
#define  BGE_ASICREV_BCM5714 131 
#define  BGE_ASICREV_BCM5714_A0 130 
#define  BGE_ASICREV_BCM5750 129 
#define  BGE_ASICREV_BCM5784 128 
 int /*<<< orphan*/  BGE_CHIPREV_5750_AX ; 
 int /*<<< orphan*/  BGE_CHIPREV_5750_BX ; 
 int /*<<< orphan*/  BGE_CHIPREV_5784_AX ; 
 int /*<<< orphan*/  BGE_IS_575X_PLUS (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_has_multiple_ports (struct bge_softc*) ; 

__attribute__((used)) static int
bge_can_use_msi(struct bge_softc *sc)
{
	int can_use_msi = 0;

	if (sc->bge_msi == 0)
		return (0);

	/* Disable MSI for polling(4). */
#ifdef DEVICE_POLLING
	return (0);
#endif
	switch (sc->bge_asicrev) {
	case BGE_ASICREV_BCM5714_A0:
	case BGE_ASICREV_BCM5714:
		/*
		 * Apparently, MSI doesn't work when these chips are
		 * configured in single-port mode.
		 */
		if (bge_has_multiple_ports(sc))
			can_use_msi = 1;
		break;
	case BGE_ASICREV_BCM5750:
		if (sc->bge_chiprev != BGE_CHIPREV_5750_AX &&
		    sc->bge_chiprev != BGE_CHIPREV_5750_BX)
			can_use_msi = 1;
		break;
	case BGE_ASICREV_BCM5784:
		/*
		 * Prevent infinite "watchdog timeout" errors
		 * in some MacBook Pro and make it work out-of-the-box.
		 */
		if (sc->bge_chiprev == BGE_CHIPREV_5784_AX)
			break;
		/* FALLTHROUGH */
	default:
		if (BGE_IS_575X_PLUS(sc))
			can_use_msi = 1;
	}
	return (can_use_msi);
}