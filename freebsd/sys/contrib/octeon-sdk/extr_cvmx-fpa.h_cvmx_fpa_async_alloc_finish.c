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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SYNCIOBDMA ; 
 void* cvmx_fpa_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_likely (int /*<<< orphan*/ ) ; 
 void* cvmx_phys_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_scratch_read64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *cvmx_fpa_async_alloc_finish(uint64_t scr_addr, uint64_t pool)
{
    uint64_t address;

    CVMX_SYNCIOBDMA;

    address = cvmx_scratch_read64(scr_addr);
    if (cvmx_likely(address))
        return cvmx_phys_to_ptr(address);
    else
        return cvmx_fpa_alloc(pool);
}