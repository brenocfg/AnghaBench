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
struct TYPE_2__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

__attribute__((used)) static int cvmx_uart_simulator_p(void)
{
#ifndef CVMX_BUILD_FOR_TOOLCHAIN
  return cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM;
#else
  extern int __octeon_simulator_p;
  return __octeon_simulator_p;
#endif
}