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
struct TYPE_2__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_BBGW_REF 135 
#define  CVMX_BOARD_TYPE_CN3005_EVB_HS5 134 
#define  CVMX_BOARD_TYPE_CN3010_EVB_HS5 133 
#define  CVMX_BOARD_TYPE_CUST_DSR1000N 132 
#define  CVMX_BOARD_TYPE_EBH3000 131 
#define  CVMX_BOARD_TYPE_EBH3100 130 
#define  CVMX_BOARD_TYPE_NAO38 129 
#define  CVMX_BOARD_TYPE_THUNDER 128 
 TYPE_1__* octeon_bootinfo ; 
 scalar_t__ of_machine_is_compatible (char*) ; 

const char *octeon_get_pci_interrupts(void)
{
	/*
	 * Returning an empty string causes the interrupts to be
	 * routed based on the PCI specification. From the PCI spec:
	 *
	 * INTA# of Device Number 0 is connected to IRQW on the system
	 * board.  (Device Number has no significance regarding being
	 * located on the system board or in a connector.) INTA# of
	 * Device Number 1 is connected to IRQX on the system
	 * board. INTA# of Device Number 2 is connected to IRQY on the
	 * system board. INTA# of Device Number 3 is connected to IRQZ
	 * on the system board. The table below describes how each
	 * agent's INTx# lines are connected to the system board
	 * interrupt lines. The following equation can be used to
	 * determine to which INTx# signal on the system board a given
	 * device's INTx# line(s) is connected.
	 *
	 * MB = (D + I) MOD 4 MB = System board Interrupt (IRQW = 0,
	 * IRQX = 1, IRQY = 2, and IRQZ = 3) D = Device Number I =
	 * Interrupt Number (INTA# = 0, INTB# = 1, INTC# = 2, and
	 * INTD# = 3)
	 */
	if (of_machine_is_compatible("dlink,dsr-500n"))
		return "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
	switch (octeon_bootinfo->board_type) {
	case CVMX_BOARD_TYPE_NAO38:
		/* This is really the NAC38 */
		return "AAAAADABAAAAAAAAAAAAAAAAAAAAAAAA";
	case CVMX_BOARD_TYPE_EBH3100:
	case CVMX_BOARD_TYPE_CN3010_EVB_HS5:
	case CVMX_BOARD_TYPE_CN3005_EVB_HS5:
		return "AAABAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	case CVMX_BOARD_TYPE_BBGW_REF:
		return "AABCD";
	case CVMX_BOARD_TYPE_CUST_DSR1000N:
		return "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
	case CVMX_BOARD_TYPE_THUNDER:
	case CVMX_BOARD_TYPE_EBH3000:
	default:
		return "";
	}
}