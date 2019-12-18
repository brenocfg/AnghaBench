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
struct tmds_config {int /*<<< orphan*/  pad_ctls; int /*<<< orphan*/  peak_c; int /*<<< orphan*/  drive_c; int /*<<< orphan*/  pe_c; int /*<<< orphan*/  pll1; int /*<<< orphan*/  pll0; } ;
struct hdmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_NV_PDISP_PE_CURRENT ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_IO_PEAK_CURRENT ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_LANE_DRIVE_CURRENT ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_PAD_CTLS0 ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_PLL0 ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_PLL1 ; 
 int /*<<< orphan*/  WR4 (struct hdmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tmds_init(struct hdmi_softc *sc, const struct tmds_config *tmds)
{

	WR4(sc, HDMI_NV_PDISP_SOR_PLL0, tmds->pll0);
	WR4(sc, HDMI_NV_PDISP_SOR_PLL1, tmds->pll1);
	WR4(sc, HDMI_NV_PDISP_PE_CURRENT, tmds->pe_c);
	WR4(sc, HDMI_NV_PDISP_SOR_LANE_DRIVE_CURRENT, tmds->drive_c);
	WR4(sc, HDMI_NV_PDISP_SOR_IO_PEAK_CURRENT, tmds->peak_c);
	WR4(sc, HDMI_NV_PDISP_SOR_PAD_CTLS0, tmds->pad_ctls);
}