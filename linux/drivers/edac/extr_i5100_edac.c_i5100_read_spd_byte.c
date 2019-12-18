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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  I5100_SPDCMD ; 
 int /*<<< orphan*/  I5100_SPDDATA ; 
 int /*<<< orphan*/  i5100_spdcmd_create (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i5100_spddata_busy (int /*<<< orphan*/ ) ; 
 int i5100_spddata_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i5100_spddata_rdo (int /*<<< orphan*/ ) ; 
 scalar_t__ i5100_spddata_sbe (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int i5100_read_spd_byte(const struct mem_ctl_info *mci,
			       u8 ch, u8 slot, u8 addr, u8 *byte)
{
	struct i5100_priv *priv = mci->pvt_info;
	u16 w;
	unsigned long et;

	pci_read_config_word(priv->mc, I5100_SPDDATA, &w);
	if (i5100_spddata_busy(w))
		return -1;

	pci_write_config_dword(priv->mc, I5100_SPDCMD,
			       i5100_spdcmd_create(0xa, 1, ch * 4 + slot, addr,
						   0, 0));

	/* wait up to 100ms */
	et = jiffies + HZ / 10;
	udelay(100);
	while (1) {
		pci_read_config_word(priv->mc, I5100_SPDDATA, &w);
		if (!i5100_spddata_busy(w))
			break;
		udelay(100);
	}

	if (!i5100_spddata_rdo(w) || i5100_spddata_sbe(w))
		return -1;

	*byte = i5100_spddata_data(w);

	return 0;
}