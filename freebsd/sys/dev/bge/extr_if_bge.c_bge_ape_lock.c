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
struct bge_softc {int bge_mfw_flags; scalar_t__ bge_asicrev; int bge_func_addr; int /*<<< orphan*/  bge_dev; } ;

/* Variables and functions */
 int APE_READ_4 (struct bge_softc*,int) ; 
 int /*<<< orphan*/  APE_WRITE_4 (struct bge_softc*,int,int) ; 
#define  BGE_APE_LOCK_GPIO 134 
 int BGE_APE_LOCK_GRANT ; 
#define  BGE_APE_LOCK_GRC 133 
#define  BGE_APE_LOCK_MEM 132 
#define  BGE_APE_LOCK_PHY0 131 
#define  BGE_APE_LOCK_PHY1 130 
#define  BGE_APE_LOCK_PHY2 129 
#define  BGE_APE_LOCK_PHY3 128 
 int BGE_APE_LOCK_REQ ; 
 int BGE_APE_LOCK_REQ_DRIVER0 ; 
 int BGE_APE_PER_LOCK_GRANT ; 
 int BGE_APE_PER_LOCK_REQ ; 
 scalar_t__ BGE_ASICREV_BCM5761 ; 
 int BGE_MFW_ON_APE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 

__attribute__((used)) static int
bge_ape_lock(struct bge_softc *sc, int locknum)
{
	uint32_t bit, gnt, req, status;
	int i, off;

	if ((sc->bge_mfw_flags & BGE_MFW_ON_APE) == 0)
		return (0);

	/* Lock request/grant registers have different bases. */
	if (sc->bge_asicrev == BGE_ASICREV_BCM5761) {
		req = BGE_APE_LOCK_REQ;
		gnt = BGE_APE_LOCK_GRANT;
	} else {
		req = BGE_APE_PER_LOCK_REQ;
		gnt = BGE_APE_PER_LOCK_GRANT;
	}

	off = 4 * locknum;

	switch (locknum) {
	case BGE_APE_LOCK_GPIO:
		/* Lock required when using GPIO. */
		if (sc->bge_asicrev == BGE_ASICREV_BCM5761)
			return (0);
		if (sc->bge_func_addr == 0)
			bit = BGE_APE_LOCK_REQ_DRIVER0;
		else
			bit = (1 << sc->bge_func_addr);
		break;
	case BGE_APE_LOCK_GRC:
		/* Lock required to reset the device. */
		if (sc->bge_func_addr == 0)
			bit = BGE_APE_LOCK_REQ_DRIVER0;
		else
			bit = (1 << sc->bge_func_addr);
		break;
	case BGE_APE_LOCK_MEM:
		/* Lock required when accessing certain APE memory. */
		if (sc->bge_func_addr == 0)
			bit = BGE_APE_LOCK_REQ_DRIVER0;
		else
			bit = (1 << sc->bge_func_addr);
		break;
	case BGE_APE_LOCK_PHY0:
	case BGE_APE_LOCK_PHY1:
	case BGE_APE_LOCK_PHY2:
	case BGE_APE_LOCK_PHY3:
		/* Lock required when accessing PHYs. */
		bit = BGE_APE_LOCK_REQ_DRIVER0;
		break;
	default:
		return (EINVAL);
	}

	/* Request a lock. */
	APE_WRITE_4(sc, req + off, bit);

	/* Wait up to 1 second to acquire lock. */
	for (i = 0; i < 20000; i++) {
		status = APE_READ_4(sc, gnt + off);
		if (status == bit)
			break;
		DELAY(50);
	}

	/* Handle any errors. */
	if (status != bit) {
		device_printf(sc->bge_dev, "APE lock %d request failed! "
		    "request = 0x%04x[0x%04x], status = 0x%04x[0x%04x]\n",
		    locknum, req + off, bit & 0xFFFF, gnt + off,
		    status & 0xFFFF);
		/* Revoke the lock request. */
		APE_WRITE_4(sc, gnt + off, bit);
		return (EBUSY);
	}

	return (0);
}