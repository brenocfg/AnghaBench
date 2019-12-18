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
struct ti_softc {int ti_hwrev; int /*<<< orphan*/  ti_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct ti_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_CPU_PROGRAM_COUNTER ; 
 int /*<<< orphan*/  TI_FIRMWARE_FIX ; 
 int /*<<< orphan*/  TI_FIRMWARE_MAJOR ; 
 int /*<<< orphan*/  TI_FIRMWARE_MINOR ; 
#define  TI_HWREV_TIGON 129 
#define  TI_HWREV_TIGON_II 128 
 int /*<<< orphan*/  TI_LOCK_ASSERT (struct ti_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ti_mem_write (struct ti_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_mem_zero (struct ti_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tigon2FwBssAddr ; 
 int /*<<< orphan*/  tigon2FwBssLen ; 
 int /*<<< orphan*/  tigon2FwData ; 
 int /*<<< orphan*/  tigon2FwDataAddr ; 
 int /*<<< orphan*/  tigon2FwDataLen ; 
 int /*<<< orphan*/  tigon2FwReleaseFix ; 
 int /*<<< orphan*/  tigon2FwReleaseMajor ; 
 int /*<<< orphan*/  tigon2FwReleaseMinor ; 
 int /*<<< orphan*/  tigon2FwRodata ; 
 int /*<<< orphan*/  tigon2FwRodataAddr ; 
 int /*<<< orphan*/  tigon2FwRodataLen ; 
 int /*<<< orphan*/  tigon2FwSbssAddr ; 
 int /*<<< orphan*/  tigon2FwSbssLen ; 
 int /*<<< orphan*/  tigon2FwStartAddr ; 
 int /*<<< orphan*/  tigon2FwText ; 
 int /*<<< orphan*/  tigon2FwTextAddr ; 
 int /*<<< orphan*/  tigon2FwTextLen ; 
 int /*<<< orphan*/  tigonFwBssAddr ; 
 int /*<<< orphan*/  tigonFwBssLen ; 
 int /*<<< orphan*/  tigonFwData ; 
 int /*<<< orphan*/  tigonFwDataAddr ; 
 int /*<<< orphan*/  tigonFwDataLen ; 
 int /*<<< orphan*/  tigonFwReleaseFix ; 
 int /*<<< orphan*/  tigonFwReleaseMajor ; 
 int /*<<< orphan*/  tigonFwReleaseMinor ; 
 int /*<<< orphan*/  tigonFwRodata ; 
 int /*<<< orphan*/  tigonFwRodataAddr ; 
 int /*<<< orphan*/  tigonFwRodataLen ; 
 int /*<<< orphan*/  tigonFwSbssAddr ; 
 int /*<<< orphan*/  tigonFwSbssLen ; 
 int /*<<< orphan*/  tigonFwStartAddr ; 
 int /*<<< orphan*/  tigonFwText ; 
 int /*<<< orphan*/  tigonFwTextAddr ; 
 int /*<<< orphan*/  tigonFwTextLen ; 

__attribute__((used)) static void
ti_loadfw(struct ti_softc *sc)
{

	TI_LOCK_ASSERT(sc);

	switch (sc->ti_hwrev) {
	case TI_HWREV_TIGON:
		if (tigonFwReleaseMajor != TI_FIRMWARE_MAJOR ||
		    tigonFwReleaseMinor != TI_FIRMWARE_MINOR ||
		    tigonFwReleaseFix != TI_FIRMWARE_FIX) {
			device_printf(sc->ti_dev, "firmware revision mismatch; "
			    "want %d.%d.%d, got %d.%d.%d\n",
			    TI_FIRMWARE_MAJOR, TI_FIRMWARE_MINOR,
			    TI_FIRMWARE_FIX, tigonFwReleaseMajor,
			    tigonFwReleaseMinor, tigonFwReleaseFix);
			return;
		}
		ti_mem_write(sc, tigonFwTextAddr, tigonFwTextLen, tigonFwText);
		ti_mem_write(sc, tigonFwDataAddr, tigonFwDataLen, tigonFwData);
		ti_mem_write(sc, tigonFwRodataAddr, tigonFwRodataLen,
		    tigonFwRodata);
		ti_mem_zero(sc, tigonFwBssAddr, tigonFwBssLen);
		ti_mem_zero(sc, tigonFwSbssAddr, tigonFwSbssLen);
		CSR_WRITE_4(sc, TI_CPU_PROGRAM_COUNTER, tigonFwStartAddr);
		break;
	case TI_HWREV_TIGON_II:
		if (tigon2FwReleaseMajor != TI_FIRMWARE_MAJOR ||
		    tigon2FwReleaseMinor != TI_FIRMWARE_MINOR ||
		    tigon2FwReleaseFix != TI_FIRMWARE_FIX) {
			device_printf(sc->ti_dev, "firmware revision mismatch; "
			    "want %d.%d.%d, got %d.%d.%d\n",
			    TI_FIRMWARE_MAJOR, TI_FIRMWARE_MINOR,
			    TI_FIRMWARE_FIX, tigon2FwReleaseMajor,
			    tigon2FwReleaseMinor, tigon2FwReleaseFix);
			return;
		}
		ti_mem_write(sc, tigon2FwTextAddr, tigon2FwTextLen,
		    tigon2FwText);
		ti_mem_write(sc, tigon2FwDataAddr, tigon2FwDataLen,
		    tigon2FwData);
		ti_mem_write(sc, tigon2FwRodataAddr, tigon2FwRodataLen,
		    tigon2FwRodata);
		ti_mem_zero(sc, tigon2FwBssAddr, tigon2FwBssLen);
		ti_mem_zero(sc, tigon2FwSbssAddr, tigon2FwSbssLen);
		CSR_WRITE_4(sc, TI_CPU_PROGRAM_COUNTER, tigon2FwStartAddr);
		break;
	default:
		device_printf(sc->ti_dev,
		    "can't load firmware: unknown hardware rev\n");
		break;
	}
}