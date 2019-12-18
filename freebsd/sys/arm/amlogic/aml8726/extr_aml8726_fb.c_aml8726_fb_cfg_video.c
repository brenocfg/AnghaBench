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
struct TYPE_2__ {int fb_width; int fb_height; } ;
struct aml8726_fb_softc {TYPE_1__ info; } ;

/* Variables and functions */
 int AML_CAV_OSD1_INDEX ; 
 int /*<<< orphan*/  AML_VIU_OSD1_BLK0_CFG_W0_REG ; 
 int /*<<< orphan*/  AML_VIU_OSD1_BLK0_CFG_W1_REG ; 
 int /*<<< orphan*/  AML_VIU_OSD1_BLK0_CFG_W2_REG ; 
 int /*<<< orphan*/  AML_VIU_OSD1_BLK0_CFG_W3_REG ; 
 int /*<<< orphan*/  AML_VIU_OSD1_BLK0_CFG_W4_REG ; 
 int /*<<< orphan*/  AML_VIU_OSD1_CTRL_REG ; 
 int /*<<< orphan*/  AML_VIU_OSD1_FIFO_CTRL_REG ; 
 int /*<<< orphan*/  AML_VIU_OSD2_CTRL_REG ; 
 int /*<<< orphan*/  AML_VIU_OSD2_FIFO_CTRL_REG ; 
 int AML_VIU_OSD_BLK_CFG_W0_BLKMODE_24 ; 
 int AML_VIU_OSD_BLK_CFG_W0_CMATRIX_RGB ; 
 int AML_VIU_OSD_BLK_CFG_W0_INDEX_SHIFT ; 
 int AML_VIU_OSD_BLK_CFG_W0_LITTLE_ENDIAN ; 
 int AML_VIU_OSD_BLK_CFG_W0_RGB_EN ; 
 int AML_VIU_OSD_BLK_CFG_W1_X_END_MASK ; 
 int AML_VIU_OSD_BLK_CFG_W1_X_END_SHIFT ; 
 int AML_VIU_OSD_BLK_CFG_W1_X_START_MASK ; 
 int AML_VIU_OSD_BLK_CFG_W1_X_START_SHIFT ; 
 int AML_VIU_OSD_BLK_CFG_W2_Y_END_MASK ; 
 int AML_VIU_OSD_BLK_CFG_W2_Y_END_SHIFT ; 
 int AML_VIU_OSD_BLK_CFG_W2_Y_START_MASK ; 
 int AML_VIU_OSD_BLK_CFG_W2_Y_START_SHIFT ; 
 int AML_VIU_OSD_BLK_CFG_W3_H_END_MASK ; 
 int AML_VIU_OSD_BLK_CFG_W3_H_END_SHIFT ; 
 int AML_VIU_OSD_BLK_CFG_W3_H_START_MASK ; 
 int AML_VIU_OSD_BLK_CFG_W3_H_START_SHIFT ; 
 int AML_VIU_OSD_BLK_CFG_W4_V_END_MASK ; 
 int AML_VIU_OSD_BLK_CFG_W4_V_END_SHIFT ; 
 int AML_VIU_OSD_BLK_CFG_W4_V_START_MASK ; 
 int AML_VIU_OSD_BLK_CFG_W4_V_START_SHIFT ; 
 int AML_VIU_OSD_CTRL_GLOBAL_ALPHA_SHIFT ; 
 int AML_VIU_OSD_CTRL_OSD_BLK_EN_MASK ; 
 int AML_VIU_OSD_CTRL_OSD_BLK_EN_SHIFT ; 
 int AML_VIU_OSD_CTRL_OSD_EN ; 
 int AML_VIU_OSD_FIFO_CTRL_BURST_LEN_64 ; 
 int AML_VIU_OSD_FIFO_CTRL_DEPTH_SHIFT ; 
 int AML_VIU_OSD_FIFO_CTRL_HOLD_LINES_SHIFT ; 
 int AML_VPP_MISC_OSD1_POSTBLEND ; 
 int AML_VPP_MISC_OSD2_POSTBLEND ; 
 int AML_VPP_MISC_POSTBLEND_EN ; 
 int AML_VPP_MISC_PREBLEND_EN ; 
 int /*<<< orphan*/  AML_VPP_MISC_REG ; 
 int AML_VPP_MISC_VD1_POSTBLEND ; 
 int AML_VPP_MISC_VD2_POSTBLEND ; 
 int VIU_READ_4 (struct aml8726_fb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIU_WRITE_4 (struct aml8726_fb_softc*,int /*<<< orphan*/ ,int) ; 
 int VPP_READ_4 (struct aml8726_fb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPP_WRITE_4 (struct aml8726_fb_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
aml8726_fb_cfg_video(struct aml8726_fb_softc *sc)
{
	uint32_t value;

	/*
	 * basic initialization
	 *
	 * The fifo depth is in units of 8 so programming 32
	 * sets the depth to 256.
	 */

	value = (32 << AML_VIU_OSD_FIFO_CTRL_DEPTH_SHIFT);
	value |= AML_VIU_OSD_FIFO_CTRL_BURST_LEN_64;
	value |= (4 << AML_VIU_OSD_FIFO_CTRL_HOLD_LINES_SHIFT);

	VIU_WRITE_4(sc, AML_VIU_OSD1_FIFO_CTRL_REG, value);
	VIU_WRITE_4(sc, AML_VIU_OSD2_FIFO_CTRL_REG, value);

	value = VPP_READ_4(sc, AML_VPP_MISC_REG);

	value &= ~AML_VPP_MISC_PREBLEND_EN;
	value |= AML_VPP_MISC_POSTBLEND_EN;
	value &= ~(AML_VPP_MISC_OSD1_POSTBLEND | AML_VPP_MISC_OSD2_POSTBLEND
	    | AML_VPP_MISC_VD1_POSTBLEND | AML_VPP_MISC_VD2_POSTBLEND);

	VPP_WRITE_4(sc, AML_VPP_MISC_REG, value);

	value = AML_VIU_OSD_CTRL_OSD_EN;
	value |= (0xff << AML_VIU_OSD_CTRL_GLOBAL_ALPHA_SHIFT);

	VIU_WRITE_4(sc, AML_VIU_OSD1_CTRL_REG, value);
	VIU_WRITE_4(sc, AML_VIU_OSD2_CTRL_REG, value);

	/* color mode for OSD1 block 0 */

	value = (AML_CAV_OSD1_INDEX << AML_VIU_OSD_BLK_CFG_W0_INDEX_SHIFT)
	    | AML_VIU_OSD_BLK_CFG_W0_LITTLE_ENDIAN
	    | AML_VIU_OSD_BLK_CFG_W0_BLKMODE_24
	    | AML_VIU_OSD_BLK_CFG_W0_RGB_EN
	    | AML_VIU_OSD_BLK_CFG_W0_CMATRIX_RGB;

	VIU_WRITE_4(sc, AML_VIU_OSD1_BLK0_CFG_W0_REG, value);

	/* geometry / scaling for OSD1 block 0 */

	value = ((sc->info.fb_width - 1) << AML_VIU_OSD_BLK_CFG_W1_X_END_SHIFT)
	    & AML_VIU_OSD_BLK_CFG_W1_X_END_MASK;
	value |= (0 << AML_VIU_OSD_BLK_CFG_W1_X_START_SHIFT)
	    & AML_VIU_OSD_BLK_CFG_W1_X_START_MASK;

	VIU_WRITE_4(sc, AML_VIU_OSD1_BLK0_CFG_W1_REG, value);

	value = ((sc->info.fb_height - 1) << AML_VIU_OSD_BLK_CFG_W2_Y_END_SHIFT)
	    & AML_VIU_OSD_BLK_CFG_W2_Y_END_MASK;
	value |= (0 << AML_VIU_OSD_BLK_CFG_W2_Y_START_SHIFT)
	    & AML_VIU_OSD_BLK_CFG_W2_Y_START_MASK;

	VIU_WRITE_4(sc, AML_VIU_OSD1_BLK0_CFG_W2_REG, value);

	value = ((sc->info.fb_width - 1) << AML_VIU_OSD_BLK_CFG_W3_H_END_SHIFT)
	    & AML_VIU_OSD_BLK_CFG_W3_H_END_MASK;
	value |= (0 << AML_VIU_OSD_BLK_CFG_W3_H_START_SHIFT)
	    & AML_VIU_OSD_BLK_CFG_W3_H_START_MASK;

	VIU_WRITE_4(sc, AML_VIU_OSD1_BLK0_CFG_W3_REG, value);

	value = ((sc->info.fb_height - 1) << AML_VIU_OSD_BLK_CFG_W4_V_END_SHIFT)
	    & AML_VIU_OSD_BLK_CFG_W4_V_END_MASK;
	value |= (0 << AML_VIU_OSD_BLK_CFG_W4_V_START_SHIFT)
	    & AML_VIU_OSD_BLK_CFG_W4_V_START_MASK;

	VIU_WRITE_4(sc, AML_VIU_OSD1_BLK0_CFG_W4_REG, value);

	/* Enable the OSD block now that it's fully configured */

	value = VIU_READ_4(sc, AML_VIU_OSD1_CTRL_REG);

	value &= ~AML_VIU_OSD_CTRL_OSD_BLK_EN_MASK;
	value |= 1 << AML_VIU_OSD_CTRL_OSD_BLK_EN_SHIFT;

	VIU_WRITE_4(sc, AML_VIU_OSD1_CTRL_REG, value);

	/* enable video processing of OSD1 */

	value = VPP_READ_4(sc, AML_VPP_MISC_REG);

	value |= AML_VPP_MISC_OSD1_POSTBLEND;

	VPP_WRITE_4(sc, AML_VPP_MISC_REG, value);
}