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
struct cs2000_priv {int dummy; } ;

/* Variables and functions */
 int AUXOUTDIS ; 
 int CLKOUTDIS ; 
 int /*<<< orphan*/  DEVICE_CTRL ; 
 int cs2000_bset (struct cs2000_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int cs2000_clk_out_enable(struct cs2000_priv *priv, bool enable)
{
	/* enable both AUX_OUT, CLK_OUT */
	return cs2000_bset(priv, DEVICE_CTRL,
			   (AUXOUTDIS | CLKOUTDIS),
			   enable ? 0 :
			   (AUXOUTDIS | CLKOUTDIS));
}