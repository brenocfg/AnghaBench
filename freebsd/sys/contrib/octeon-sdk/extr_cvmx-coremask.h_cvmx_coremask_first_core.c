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
 scalar_t__ cvmx_coremask_is_member (unsigned int) ; 
 unsigned int cvmx_coremask_numcores (scalar_t__) ; 
 scalar_t__ cvmx_get_core_num () ; 

__attribute__((used)) static inline int cvmx_coremask_first_core(unsigned int coremask)
{
    return cvmx_coremask_is_member(coremask)
        && ((cvmx_get_core_num() == 0) ||
            ((cvmx_coremask_numcores(cvmx_get_core_num()) & coremask) == 0));
}