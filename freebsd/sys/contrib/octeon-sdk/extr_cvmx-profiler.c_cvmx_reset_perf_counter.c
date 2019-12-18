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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  COP0_PERFVALUE0 ; 
 int /*<<< orphan*/  COP0_PERFVALUE1 ; 
 int /*<<< orphan*/  CVMX_MT_COP0 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void cvmx_reset_perf_counter(int pf, uint64_t events)
{
    uint64_t pfc;
    pfc = (1ull << 63) - events;
 	
    if (!pf) {
        CVMX_MT_COP0(pfc, COP0_PERFVALUE0);
    } else
        CVMX_MT_COP0(pfc, COP0_PERFVALUE1);
}