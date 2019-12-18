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
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CNF7XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIM_MAGIC_GET_IOFREQ ; 
 int __cvmx_sim_magic_return (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvmx_sim_magic_get_iofreq(void)
{
    CVMX_SYNC;

    if (OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF7XXX))
       return  __cvmx_sim_magic_return(SIM_MAGIC_GET_IOFREQ);
    else
       return 0;
}