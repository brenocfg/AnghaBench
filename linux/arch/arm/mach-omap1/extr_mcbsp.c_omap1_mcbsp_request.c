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

/* Variables and functions */
 int DPS_RSTCT2_PER_EN ; 
 int /*<<< orphan*/  DSP_RSTCT2 ; 
 int DSP_RSTCT2_WD_PER_EN ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  api_clk ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dsp_clk ; 
 int /*<<< orphan*/  dsp_use ; 

__attribute__((used)) static void omap1_mcbsp_request(unsigned int id)
{
	/*
	 * On 1510, 1610 and 1710, McBSP1 and McBSP3
	 * are DSP public peripherals.
	 */
	if (id == 0 || id == 2) {
		if (dsp_use++ == 0) {
			api_clk = clk_get(NULL, "api_ck");
			dsp_clk = clk_get(NULL, "dsp_ck");
			if (!IS_ERR(api_clk) && !IS_ERR(dsp_clk)) {
				clk_enable(api_clk);
				clk_enable(dsp_clk);

				/*
				 * DSP external peripheral reset
				 * FIXME: This should be moved to dsp code
				 */
				__raw_writew(__raw_readw(DSP_RSTCT2) | DPS_RSTCT2_PER_EN |
						DSP_RSTCT2_WD_PER_EN, DSP_RSTCT2);
			}
		}
	}
}