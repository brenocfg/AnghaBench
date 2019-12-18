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
struct ahci_host_priv {scalar_t__* clks; } ;

/* Variables and functions */
 int AHCI_MAX_CLKS ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 

int ahci_platform_enable_clks(struct ahci_host_priv *hpriv)
{
	int c, rc;

	for (c = 0; c < AHCI_MAX_CLKS && hpriv->clks[c]; c++) {
		rc = clk_prepare_enable(hpriv->clks[c]);
		if (rc)
			goto disable_unprepare_clk;
	}
	return 0;

disable_unprepare_clk:
	while (--c >= 0)
		clk_disable_unprepare(hpriv->clks[c]);
	return rc;
}