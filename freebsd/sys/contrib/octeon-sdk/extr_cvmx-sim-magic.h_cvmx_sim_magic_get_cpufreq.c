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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SYNC ; 
 int /*<<< orphan*/  SIM_MAGIC_GET_CPUFREQ ; 
 int __cvmx_sim_magic_return (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvmx_sim_magic_get_cpufreq(void)
{
    CVMX_SYNC;

    return  __cvmx_sim_magic_return(SIM_MAGIC_GET_CPUFREQ);
}