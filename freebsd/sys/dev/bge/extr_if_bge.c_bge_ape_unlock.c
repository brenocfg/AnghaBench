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
typedef  int uint32_t ;
struct bge_softc {int bge_mfw_flags; scalar_t__ bge_asicrev; int bge_func_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APE_WRITE_4 (struct bge_softc*,int,int) ; 
#define  BGE_APE_LOCK_GPIO 134 
 int BGE_APE_LOCK_GRANT ; 
 int BGE_APE_LOCK_GRANT_DRIVER0 ; 
#define  BGE_APE_LOCK_GRC 133 
#define  BGE_APE_LOCK_MEM 132 
#define  BGE_APE_LOCK_PHY0 131 
#define  BGE_APE_LOCK_PHY1 130 
#define  BGE_APE_LOCK_PHY2 129 
#define  BGE_APE_LOCK_PHY3 128 
 int BGE_APE_PER_LOCK_GRANT ; 
 scalar_t__ BGE_ASICREV_BCM5761 ; 
 int BGE_MFW_ON_APE ; 

__attribute__((used)) static void
bge_ape_unlock(struct bge_softc *sc, int locknum)
{
	uint32_t bit, gnt;
	int off;

	if ((sc->bge_mfw_flags & BGE_MFW_ON_APE) == 0)
		return;

	if (sc->bge_asicrev == BGE_ASICREV_BCM5761)
		gnt = BGE_APE_LOCK_GRANT;
	else
		gnt = BGE_APE_PER_LOCK_GRANT;

	off = 4 * locknum;

	switch (locknum) {
	case BGE_APE_LOCK_GPIO:
		if (sc->bge_asicrev == BGE_ASICREV_BCM5761)
			return;
		if (sc->bge_func_addr == 0)
			bit = BGE_APE_LOCK_GRANT_DRIVER0;
		else
			bit = (1 << sc->bge_func_addr);
		break;
	case BGE_APE_LOCK_GRC:
		if (sc->bge_func_addr == 0)
			bit = BGE_APE_LOCK_GRANT_DRIVER0;
		else
			bit = (1 << sc->bge_func_addr);
		break;
	case BGE_APE_LOCK_MEM:
		if (sc->bge_func_addr == 0)
			bit = BGE_APE_LOCK_GRANT_DRIVER0;
		else
			bit = (1 << sc->bge_func_addr);
		break;
	case BGE_APE_LOCK_PHY0:
	case BGE_APE_LOCK_PHY1:
	case BGE_APE_LOCK_PHY2:
	case BGE_APE_LOCK_PHY3:
		bit = BGE_APE_LOCK_GRANT_DRIVER0;
		break;
	default:
		return;
	}

	APE_WRITE_4(sc, gnt + off, bit);
}