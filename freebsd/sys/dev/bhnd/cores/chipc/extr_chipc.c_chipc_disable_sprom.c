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
struct TYPE_2__ {int nvram_src; } ;
struct chipc_softc {scalar_t__ sprom_refcnt; TYPE_1__ caps; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BHND_NVRAM_SRC_OTP 129 
#define  BHND_NVRAM_SRC_SPROM 128 
 int /*<<< orphan*/  CHIPC_LOCK (struct chipc_softc*) ; 
 int /*<<< orphan*/  CHIPC_UNLOCK (struct chipc_softc*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  chipc_disable_otp_power (struct chipc_softc*) ; 
 int /*<<< orphan*/  chipc_disable_sprom_pins (struct chipc_softc*) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chipc_disable_sprom(device_t dev)
{
	struct chipc_softc	*sc;

	sc = device_get_softc(dev);
	CHIPC_LOCK(sc);

	/* Check reference count, skip disable if in-use. */
	KASSERT(sc->sprom_refcnt > 0, ("sprom refcnt overrelease"));
	sc->sprom_refcnt--;
	if (sc->sprom_refcnt > 0) {
		CHIPC_UNLOCK(sc);
		return;
	}

	switch (sc->caps.nvram_src) {
	case BHND_NVRAM_SRC_SPROM:
		chipc_disable_sprom_pins(sc);
		break;
	case BHND_NVRAM_SRC_OTP:
		chipc_disable_otp_power(sc);
		break;
	default:
		break;
	}


	CHIPC_UNLOCK(sc);
}