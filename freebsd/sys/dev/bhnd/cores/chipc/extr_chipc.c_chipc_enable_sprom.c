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
struct chipc_softc {int sprom_refcnt; TYPE_1__ caps; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BHND_NVRAM_SRC_OTP 129 
#define  BHND_NVRAM_SRC_SPROM 128 
 int /*<<< orphan*/  CHIPC_LOCK (struct chipc_softc*) ; 
 int /*<<< orphan*/  CHIPC_UNLOCK (struct chipc_softc*) ; 
 int chipc_enable_otp_power (struct chipc_softc*) ; 
 int chipc_enable_sprom_pins (struct chipc_softc*) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_enable_sprom(device_t dev)
{
	struct chipc_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);
	CHIPC_LOCK(sc);

	/* Already enabled? */
	if (sc->sprom_refcnt >= 1) {
		sc->sprom_refcnt++;
		CHIPC_UNLOCK(sc);

		return (0);
	}

	switch (sc->caps.nvram_src) {
	case BHND_NVRAM_SRC_SPROM:
		error = chipc_enable_sprom_pins(sc);
		break;
	case BHND_NVRAM_SRC_OTP:
		error = chipc_enable_otp_power(sc);
		break;
	default:
		error = 0;
		break;
	}

	/* Bump the reference count */
	if (error == 0)
		sc->sprom_refcnt++;

	CHIPC_UNLOCK(sc);
	return (error);
}