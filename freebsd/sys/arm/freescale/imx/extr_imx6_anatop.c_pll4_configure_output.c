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

/* Variables and functions */
 int /*<<< orphan*/  IMX6_ANALOG_CCM_PLL_AUDIO ; 
 int /*<<< orphan*/  IMX6_ANALOG_CCM_PLL_AUDIO_DENOM ; 
 int IMX6_ANALOG_CCM_PLL_AUDIO_DIV_SELECT_MASK ; 
 int IMX6_ANALOG_CCM_PLL_AUDIO_DIV_SELECT_SHIFT ; 
 int IMX6_ANALOG_CCM_PLL_AUDIO_ENABLE ; 
 int /*<<< orphan*/  IMX6_ANALOG_CCM_PLL_AUDIO_NUM ; 
 int /*<<< orphan*/  imx6_anatop_write_4 (int /*<<< orphan*/ ,int) ; 

uint32_t
pll4_configure_output(uint32_t mfi, uint32_t mfn, uint32_t mfd)
{
	int reg;

	/*
	 * Audio PLL (PLL4).
	 * PLL output frequency = Fref * (DIV_SELECT + NUM/DENOM)
	 */

	reg = (IMX6_ANALOG_CCM_PLL_AUDIO_ENABLE);
	reg &= ~(IMX6_ANALOG_CCM_PLL_AUDIO_DIV_SELECT_MASK << \
		IMX6_ANALOG_CCM_PLL_AUDIO_DIV_SELECT_SHIFT);
	reg |= (mfi << IMX6_ANALOG_CCM_PLL_AUDIO_DIV_SELECT_SHIFT);
	imx6_anatop_write_4(IMX6_ANALOG_CCM_PLL_AUDIO, reg);
	imx6_anatop_write_4(IMX6_ANALOG_CCM_PLL_AUDIO_NUM, mfn);
	imx6_anatop_write_4(IMX6_ANALOG_CCM_PLL_AUDIO_DENOM, mfd);

	return (0);
}