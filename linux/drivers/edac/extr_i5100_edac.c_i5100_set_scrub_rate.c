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
typedef  int u32 ;
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {int scrub_enable; int /*<<< orphan*/  mc; int /*<<< orphan*/  i5100_scrubbing; } ;

/* Variables and functions */
 int /*<<< orphan*/  I5100_MC ; 
 int I5100_MC_SCRBEN_MASK ; 
 int /*<<< orphan*/  I5100_SCRUB_REFRESH_RATE ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int i5100_mc_scrben (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i5100_set_scrub_rate(struct mem_ctl_info *mci, u32 bandwidth)
{
	struct i5100_priv *priv = mci->pvt_info;
	u32 dw;

	pci_read_config_dword(priv->mc, I5100_MC, &dw);
	if (bandwidth) {
		priv->scrub_enable = 1;
		dw |= I5100_MC_SCRBEN_MASK;
		schedule_delayed_work(&(priv->i5100_scrubbing),
				      I5100_SCRUB_REFRESH_RATE);
	} else {
		priv->scrub_enable = 0;
		dw &= ~I5100_MC_SCRBEN_MASK;
		cancel_delayed_work(&(priv->i5100_scrubbing));
	}
	pci_write_config_dword(priv->mc, I5100_MC, dw);

	pci_read_config_dword(priv->mc, I5100_MC, &dw);

	bandwidth = 5900000 * i5100_mc_scrben(dw);

	return bandwidth;
}