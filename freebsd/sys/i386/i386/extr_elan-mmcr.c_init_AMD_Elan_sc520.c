#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct elan_mmcr {int GPTMR2CTL; int CSPFS; int GPTMR1CTL; int GPTMR1MAXCMPA; int GPTMR1MAXCMPB; scalar_t__ GPTMR2MAXCMPA; } ;
struct TYPE_3__ {int /*<<< orphan*/  ppscap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPS_CAPTUREASSERT ; 
 scalar_t__ bootverbose ; 
 struct elan_mmcr volatile* elan_mmcr ; 
 TYPE_1__ elan_pps ; 
 int /*<<< orphan*/  elan_timecounter ; 
 int kernel_sysctlbyname (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mmcrptr ; 
 scalar_t__ pmap_mapdev (int,int) ; 
 int /*<<< orphan*/  pps_init (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  tc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread0 ; 

void
init_AMD_Elan_sc520(void)
{
	u_int new;
	int i;

	mmcrptr = pmap_mapdev(0xfffef000, 0x1000);
	elan_mmcr = (volatile struct elan_mmcr *)mmcrptr;

	/*-
	 * The i8254 is driven with a nonstandard frequency which is
	 * derived thusly:
	 *   f = 32768 * 45 * 25 / 31 = 1189161.29...
	 * We use the sysctl to get the i8254 (timecounter etc) into whack.
	 */
	
	new = 1189161;
	i = kernel_sysctlbyname(&thread0, "machdep.i8254_freq", 
	    NULL, 0, &new, sizeof new, NULL, 0);
	if (bootverbose || 1)
		printf("sysctl machdep.i8254_freq=%d returns %d\n", new, i);

	/* Start GP timer #2 and use it as timecounter, hz permitting */
	elan_mmcr->GPTMR2MAXCMPA = 0;
	elan_mmcr->GPTMR2CTL = 0xc001;

#ifdef CPU_ELAN_PPS
	/* Set up GP timer #1 as pps counter */
	elan_mmcr->CSPFS &= ~0x10;
	elan_mmcr->GPTMR1CTL = 0x8000 | 0x4000 | 0x10 | 0x1;
	elan_mmcr->GPTMR1MAXCMPA = 0x0;
	elan_mmcr->GPTMR1MAXCMPB = 0x0;
	elan_pps.ppscap |= PPS_CAPTUREASSERT;
	pps_init(&elan_pps);
#endif
	tc_init(&elan_timecounter);
}