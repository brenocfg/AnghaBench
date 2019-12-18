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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  COP0_CVMCTL ; 
 int /*<<< orphan*/  CVMX_MF_COP0 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_COP0 (int,int /*<<< orphan*/ ) ; 

void cvmx_update_perfcnt_irq(void)
{
    uint64_t cvmctl;
   
    /* Clear CvmCtl[IPPCI] bit and move the Performance Counter
     * interrupt to IRQ 6
     */
    CVMX_MF_COP0(cvmctl, COP0_CVMCTL);
    cvmctl &= ~(7 << 7);
    cvmctl |= 6 << 7;
    CVMX_MT_COP0(cvmctl, COP0_CVMCTL);
}