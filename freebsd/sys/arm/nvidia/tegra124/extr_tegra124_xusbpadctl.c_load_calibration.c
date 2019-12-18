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
typedef  int /*<<< orphan*/  uint32_t ;
struct padctl_softc {int /*<<< orphan*/  hs_term_range_adj; int /*<<< orphan*/  hs_squelch_level; int /*<<< orphan*/  hs_iref_cap; int /*<<< orphan*/  hs_curr_level_123; int /*<<< orphan*/  hs_curr_level_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_XUSB_CALIB ; 
 int /*<<< orphan*/  FUSE_XUSB_CALIB_HS_CURR_LEVEL_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSE_XUSB_CALIB_HS_CURR_LEVEL_123 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSE_XUSB_CALIB_HS_IREF_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSE_XUSB_CALIB_HS_SQUELCH_LEVEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSE_XUSB_CALIB_HS_TERM_RANGE_ADJ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_fuse_read_4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
load_calibration(struct padctl_softc *sc)
{
	uint32_t reg;

	/* All XUSB pad calibrations are packed into single dword.*/
	reg = tegra_fuse_read_4(FUSE_XUSB_CALIB);
	sc->hs_curr_level_0 = FUSE_XUSB_CALIB_HS_CURR_LEVEL_0(reg);
	sc->hs_curr_level_123 = FUSE_XUSB_CALIB_HS_CURR_LEVEL_123(reg);
	sc->hs_iref_cap = FUSE_XUSB_CALIB_HS_IREF_CAP(reg);
	sc->hs_squelch_level = FUSE_XUSB_CALIB_HS_SQUELCH_LEVEL(reg);
	sc->hs_term_range_adj = FUSE_XUSB_CALIB_HS_TERM_RANGE_ADJ(reg);
}