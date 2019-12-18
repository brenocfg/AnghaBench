#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  didspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  u64; TYPE_1__ sfilldidspace; } ;
typedef  TYPE_2__ cvmx_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ADDR_DIDSPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_FULL_DID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_OCT_DID_FPA ; 
 int /*<<< orphan*/  cvmx_ptr_to_phys (void*) ; 
 int /*<<< orphan*/  cvmx_write_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_fpa_free_nosync(void *ptr, uint64_t pool, uint64_t num_cache_lines)
{
    cvmx_addr_t newptr;
    newptr.u64 = cvmx_ptr_to_phys(ptr);
    newptr.sfilldidspace.didspace = CVMX_ADDR_DIDSPACE(CVMX_FULL_DID(CVMX_OCT_DID_FPA,pool));
    asm volatile ("" : : : "memory");  /* Prevent GCC from reordering around free */
    /* value written is number of cache lines not written back */
    cvmx_write_io(newptr.u64, num_cache_lines);
}