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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NFORCE2_DELAY ; 
 unsigned int NFORCE2_MIN_FSB ; 
 int /*<<< orphan*/  NFORCE2_PLLADR ; 
 int /*<<< orphan*/  NFORCE2_PLLENABLE ; 
 unsigned int max_fsb ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 unsigned int min_fsb ; 
 int nforce2_calc_pll (unsigned int) ; 
 int /*<<< orphan*/  nforce2_dev ; 
 unsigned int nforce2_fsb_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nforce2_write_pll (int) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int nforce2_set_fsb(unsigned int fsb)
{
	u32 temp = 0;
	unsigned int tfsb;
	int diff;
	int pll = 0;

	if ((fsb > max_fsb) || (fsb < NFORCE2_MIN_FSB)) {
		pr_err("FSB %d is out of range!\n", fsb);
		return -EINVAL;
	}

	tfsb = nforce2_fsb_read(0);
	if (!tfsb) {
		pr_err("Error while reading the FSB\n");
		return -EINVAL;
	}

	/* First write? Then set actual value */
	pci_read_config_byte(nforce2_dev, NFORCE2_PLLENABLE, (u8 *)&temp);
	if (!temp) {
		pll = nforce2_calc_pll(tfsb);

		if (pll < 0)
			return -EINVAL;

		nforce2_write_pll(pll);
	}

	/* Enable write access */
	temp = 0x01;
	pci_write_config_byte(nforce2_dev, NFORCE2_PLLENABLE, (u8)temp);

	diff = tfsb - fsb;

	if (!diff)
		return 0;

	while ((tfsb != fsb) && (tfsb <= max_fsb) && (tfsb >= min_fsb)) {
		if (diff < 0)
			tfsb++;
		else
			tfsb--;

		/* Calculate the PLL reg. value */
		pll = nforce2_calc_pll(tfsb);
		if (pll == -1)
			return -EINVAL;

		nforce2_write_pll(pll);
#ifdef NFORCE2_DELAY
		mdelay(NFORCE2_DELAY);
#endif
	}

	temp = 0x40;
	pci_write_config_byte(nforce2_dev, NFORCE2_PLLADR, (u8)temp);

	return 0;
}