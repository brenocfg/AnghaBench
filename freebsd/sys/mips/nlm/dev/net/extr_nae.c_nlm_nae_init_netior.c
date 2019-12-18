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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_LANE_CFG_SOFTRESET ; 
 int /*<<< orphan*/  NAE_NETIOR_MISC_CTRL1 ; 
 int /*<<< orphan*/  NAE_NETIOR_MISC_CTRL2 ; 
 int /*<<< orphan*/  NAE_NETIOR_MISC_CTRL3 ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
nlm_nae_init_netior(uint64_t nae_base, int nblocks)
{
	uint32_t ctrl1, ctrl2, ctrl3;

	if (nblocks == 5)
		ctrl3 = 0x07 << 18;
	else
		ctrl3 = 0;

	switch (nblocks) {
	case 2:
		ctrl1 = 0xff;
		ctrl2 = 0x0707;
		break;
	case 4:
	case 5:
		ctrl1 = 0xfffff;
		ctrl2 = 0x07070707;
		break;
	default:
		printf("WARNING: unsupported blocks %d\n", nblocks);
		return (-1);
	}

	nlm_write_nae_reg(nae_base, NAE_LANE_CFG_SOFTRESET, 0);
	nlm_write_nae_reg(nae_base, NAE_NETIOR_MISC_CTRL3, ctrl3);
	nlm_write_nae_reg(nae_base, NAE_NETIOR_MISC_CTRL2, ctrl2);
	nlm_write_nae_reg(nae_base, NAE_NETIOR_MISC_CTRL1, ctrl1);
	nlm_write_nae_reg(nae_base, NAE_NETIOR_MISC_CTRL1, 0x0);
	return (0);
}