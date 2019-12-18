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
typedef  int uint32_t ;
struct TYPE_2__ {int core_mask; } ;

/* Variables and functions */
 TYPE_1__* cvmx_sysinfo_get () ; 
 int octeon_get_boot_coremask () ; 

__attribute__((used)) static inline uint32_t cvmx_debug_core_mask(void)
{
#ifndef CVMX_BUILD_FOR_LINUX_KERNEL
#ifdef CVMX_BUILD_FOR_TOOLCHAIN
  extern int __octeon_core_mask;
  return __octeon_core_mask;
#endif
return cvmx_sysinfo_get()->core_mask;
#else
return octeon_get_boot_coremask ();
#endif
}