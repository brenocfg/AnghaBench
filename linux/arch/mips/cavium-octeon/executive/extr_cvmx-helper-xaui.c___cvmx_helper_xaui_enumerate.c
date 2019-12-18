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
struct TYPE_2__ {scalar_t__ hg2tx_en; } ;
union cvmx_gmxx_hg2_control {TYPE_1__ s; int /*<<< orphan*/  u64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_HG2_CONTROL (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

int __cvmx_helper_xaui_enumerate(int interface)
{
	union cvmx_gmxx_hg2_control gmx_hg2_control;

	/* If HiGig2 is enabled return 16 ports, otherwise return 1 port */
	gmx_hg2_control.u64 = cvmx_read_csr(CVMX_GMXX_HG2_CONTROL(interface));
	if (gmx_hg2_control.s.hg2tx_en)
		return 16;
	else
		return 1;
}