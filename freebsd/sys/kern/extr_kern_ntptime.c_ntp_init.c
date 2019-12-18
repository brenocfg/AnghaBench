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
struct TYPE_2__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  L_CLR (int /*<<< orphan*/ ) ; 
 scalar_t__ pps_fcount ; 
 int /*<<< orphan*/  pps_freq ; 
 TYPE_1__* pps_tf ; 
 int /*<<< orphan*/  time_freq ; 
 int /*<<< orphan*/  time_offset ; 

__attribute__((used)) static void
ntp_init(void)
{

	/*
	 * The following variables are initialized only at startup. Only
	 * those structures not cleared by the compiler need to be
	 * initialized, and these only in the simulator. In the actual
	 * kernel, any nonzero values here will quickly evaporate.
	 */
	L_CLR(time_offset);
	L_CLR(time_freq);
#ifdef PPS_SYNC
	pps_tf[0].tv_sec = pps_tf[0].tv_nsec = 0;
	pps_tf[1].tv_sec = pps_tf[1].tv_nsec = 0;
	pps_tf[2].tv_sec = pps_tf[2].tv_nsec = 0;
	pps_fcount = 0;
	L_CLR(pps_freq);
#endif /* PPS_SYNC */	   
}