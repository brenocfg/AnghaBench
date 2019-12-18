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
struct chipc_softc {int /*<<< orphan*/  core; int /*<<< orphan*/  dev; } ;
struct chipc_caps {scalar_t__ otp_size; scalar_t__ flash_type; scalar_t__ sprom; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_src ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_SRC_FLASH ; 
 int /*<<< orphan*/  BHND_NVRAM_SRC_OTP ; 
 int /*<<< orphan*/  BHND_NVRAM_SRC_SPROM ; 
 int /*<<< orphan*/  BHND_NVRAM_SRC_UNKNOWN ; 
 scalar_t__ CHIPC_FLASH_NONE ; 
 int /*<<< orphan*/  CHIPC_OTPST ; 
 int CHIPC_OTPS_GUP_HW ; 
 scalar_t__ CHIPC_QUIRK (struct chipc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIPC_SPROM_CTRL ; 
 int CHIPC_SRC_PRESENT ; 
 int /*<<< orphan*/  OTP_HND ; 
 int /*<<< orphan*/  SUPPORTS_OTP ; 
 int /*<<< orphan*/  SUPPORTS_SPROM ; 
 int bhnd_bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bhnd_nvram_src
chipc_find_nvram_src(struct chipc_softc *sc, struct chipc_caps *caps)
{
	uint32_t		 otp_st, srom_ctrl;

	/*
	 * We check for hardware presence in order of precedence. For example,
	 * SPROM is is always used in preference to internal OTP if found.
	 */
	if (CHIPC_QUIRK(sc, SUPPORTS_SPROM) && caps->sprom) {
		srom_ctrl = bhnd_bus_read_4(sc->core, CHIPC_SPROM_CTRL);
		if (srom_ctrl & CHIPC_SRC_PRESENT)
			return (BHND_NVRAM_SRC_SPROM);
	}

	/* Check for programmed OTP H/W subregion (contains SROM data) */
	if (CHIPC_QUIRK(sc, SUPPORTS_OTP) && caps->otp_size > 0) {
		/* TODO: need access to HND-OTP device */
		if (!CHIPC_QUIRK(sc, OTP_HND)) {
			device_printf(sc->dev,
			    "NVRAM unavailable: unsupported OTP controller.\n");
			return (BHND_NVRAM_SRC_UNKNOWN);
		}

		otp_st = bhnd_bus_read_4(sc->core, CHIPC_OTPST);
		if (otp_st & CHIPC_OTPS_GUP_HW)
			return (BHND_NVRAM_SRC_OTP);
	}

	/* Check for flash */
	if (caps->flash_type != CHIPC_FLASH_NONE)
		return (BHND_NVRAM_SRC_FLASH);

	/* No NVRAM hardware capability declared */
	return (BHND_NVRAM_SRC_UNKNOWN);
}