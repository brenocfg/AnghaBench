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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ fb_height; scalar_t__ fb_pbase; scalar_t__ fb_stride; } ;
struct aml8726_fb_softc {TYPE_1__ info; } ;

/* Variables and functions */
 int AML_CAV_LUT_ADDR_INDEX_SHIFT ; 
 int /*<<< orphan*/  AML_CAV_LUT_ADDR_REG ; 
 int AML_CAV_LUT_ADDR_WR_EN ; 
 int AML_CAV_LUT_DATAH_BLKMODE_LINEAR ; 
 int AML_CAV_LUT_DATAH_HEIGHT_MASK ; 
 int AML_CAV_LUT_DATAH_HEIGHT_SHIFT ; 
 int /*<<< orphan*/  AML_CAV_LUT_DATAH_REG ; 
 int AML_CAV_LUT_DATAH_WIDTH_MASK ; 
 int AML_CAV_LUT_DATAH_WIDTH_SHIFT ; 
 int /*<<< orphan*/  AML_CAV_LUT_DATAL_REG ; 
 int AML_CAV_LUT_DATAL_WIDTH_MASK ; 
 int AML_CAV_LUT_DATAL_WIDTH_SHIFT ; 
 int AML_CAV_LUT_DATAL_WIDTH_WIDTH ; 
 int AML_CAV_OSD1_INDEX ; 
 int /*<<< orphan*/  CAV_BARRIER (struct aml8726_fb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAV_WRITE_4 (struct aml8726_fb_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
aml8726_fb_cfg_canvas(struct aml8726_fb_softc *sc)
{
	uint32_t value;
	uint32_t width;

	/*
	 * The frame buffer address and width are programmed in units of 8
	 * (meaning they need to be aligned and the actual values divided
	 * by 8 prior to programming the hardware).
	 */

	width = (uint32_t)sc->info.fb_stride / 8;

	/* lower bits of the width */
	value = (width << AML_CAV_LUT_DATAL_WIDTH_SHIFT) &
	    AML_CAV_LUT_DATAL_WIDTH_MASK;

	/* physical address */
	value |= (uint32_t)sc->info.fb_pbase / 8;

	CAV_WRITE_4(sc, AML_CAV_LUT_DATAL_REG, value);

	/* upper bits of the width */
	value = ((width >> AML_CAV_LUT_DATAL_WIDTH_WIDTH) <<
	    AML_CAV_LUT_DATAH_WIDTH_SHIFT) & AML_CAV_LUT_DATAH_WIDTH_MASK;

	/* height */
	value |= ((uint32_t)sc->info.fb_height <<
	    AML_CAV_LUT_DATAH_HEIGHT_SHIFT) & AML_CAV_LUT_DATAH_HEIGHT_MASK;

	/* mode */
	value |= AML_CAV_LUT_DATAH_BLKMODE_LINEAR;

	CAV_WRITE_4(sc, AML_CAV_LUT_DATAH_REG, value);

	CAV_WRITE_4(sc, AML_CAV_LUT_ADDR_REG, (AML_CAV_LUT_ADDR_WR_EN |
	    (AML_CAV_OSD1_INDEX << AML_CAV_LUT_ADDR_INDEX_SHIFT)));

	CAV_BARRIER(sc, AML_CAV_LUT_ADDR_REG);
}