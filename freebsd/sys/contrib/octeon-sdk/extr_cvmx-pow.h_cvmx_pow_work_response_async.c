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
typedef  int /*<<< orphan*/  cvmx_wqe_t ;
struct TYPE_3__ {int /*<<< orphan*/  addr; scalar_t__ no_work; } ;
struct TYPE_4__ {TYPE_1__ s_work; int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ cvmx_pow_tag_load_resp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SYNCIOBDMA ; 
 scalar_t__ cvmx_phys_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_scratch_read64 (int) ; 

__attribute__((used)) static inline cvmx_wqe_t * cvmx_pow_work_response_async(int scr_addr)
{
    cvmx_pow_tag_load_resp_t result;

    CVMX_SYNCIOBDMA;
    result.u64 = cvmx_scratch_read64(scr_addr);

    if (result.s_work.no_work)
        return NULL;
    else
        return (cvmx_wqe_t*)cvmx_phys_to_ptr(result.s_work.addr);
}