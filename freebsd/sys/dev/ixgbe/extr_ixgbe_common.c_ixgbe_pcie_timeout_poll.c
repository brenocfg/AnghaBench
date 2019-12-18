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
struct ixgbe_hw {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
#define  IXGBE_PCIDEVCTRL2_16_32ms 136 
#define  IXGBE_PCIDEVCTRL2_16_32ms_def 135 
#define  IXGBE_PCIDEVCTRL2_17_34s 134 
#define  IXGBE_PCIDEVCTRL2_1_2ms 133 
#define  IXGBE_PCIDEVCTRL2_1_2s 132 
#define  IXGBE_PCIDEVCTRL2_260_520ms 131 
#define  IXGBE_PCIDEVCTRL2_4_8s 130 
#define  IXGBE_PCIDEVCTRL2_50_100us 129 
#define  IXGBE_PCIDEVCTRL2_65_130ms 128 
 int IXGBE_PCIDEVCTRL2_TIMEO_MASK ; 
 int /*<<< orphan*/  IXGBE_PCI_DEVICE_CONTROL2 ; 
 int IXGBE_READ_PCIE_WORD (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ixgbe_pcie_timeout_poll(struct ixgbe_hw *hw)
{
	s16 devctl2;
	u32 pollcnt;

	devctl2 = IXGBE_READ_PCIE_WORD(hw, IXGBE_PCI_DEVICE_CONTROL2);
	devctl2 &= IXGBE_PCIDEVCTRL2_TIMEO_MASK;

	switch (devctl2) {
	case IXGBE_PCIDEVCTRL2_65_130ms:
		pollcnt = 1300;		/* 130 millisec */
		break;
	case IXGBE_PCIDEVCTRL2_260_520ms:
		pollcnt = 5200;		/* 520 millisec */
		break;
	case IXGBE_PCIDEVCTRL2_1_2s:
		pollcnt = 20000;	/* 2 sec */
		break;
	case IXGBE_PCIDEVCTRL2_4_8s:
		pollcnt = 80000;	/* 8 sec */
		break;
	case IXGBE_PCIDEVCTRL2_17_34s:
		pollcnt = 34000;	/* 34 sec */
		break;
	case IXGBE_PCIDEVCTRL2_50_100us:	/* 100 microsecs */
	case IXGBE_PCIDEVCTRL2_1_2ms:		/* 2 millisecs */
	case IXGBE_PCIDEVCTRL2_16_32ms:		/* 32 millisec */
	case IXGBE_PCIDEVCTRL2_16_32ms_def:	/* 32 millisec default */
	default:
		pollcnt = 800;		/* 80 millisec minimum */
		break;
	}

	/* add 10% to spec maximum */
	return (pollcnt * 11) / 10;
}