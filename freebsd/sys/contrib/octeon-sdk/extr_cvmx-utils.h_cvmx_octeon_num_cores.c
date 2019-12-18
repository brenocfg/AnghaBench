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
 int /*<<< orphan*/  CVMX_CIU_FUSE ; 
 int cvmx_pop (int) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t cvmx_octeon_num_cores(void)
{
    uint32_t ciu_fuse = (uint32_t)cvmx_read_csr(CVMX_CIU_FUSE) & 0xffffffffull;
    return cvmx_pop(ciu_fuse);
}