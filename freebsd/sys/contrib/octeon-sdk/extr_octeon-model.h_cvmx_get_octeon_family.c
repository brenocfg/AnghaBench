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
typedef  int uint32_t ;

/* Variables and functions */
 int OCTEON_FAMILY_MASK ; 
 int OCTEON_MODEL ; 
 int cvmx_get_proc_id () ; 

__attribute__((used)) static inline uint32_t cvmx_get_octeon_family(void)
{
#if defined(USE_RUNTIME_MODEL_CHECKS) || defined(__U_BOOT__) || (defined(__linux__) && defined(__KERNEL__)) || defined(CVMX_BUILD_FOR_TOOLCHAIN) || (defined(__FreeBSD__) && defined(_KERNEL))
    return (cvmx_get_proc_id() & OCTEON_FAMILY_MASK);
#else
    return (OCTEON_MODEL & OCTEON_FAMILY_MASK);
#endif
}