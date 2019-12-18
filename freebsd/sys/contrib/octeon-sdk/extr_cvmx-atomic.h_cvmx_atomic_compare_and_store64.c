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
 int /*<<< orphan*/  CVMX_SYNCWS ; 
 int /*<<< orphan*/  cvmx_atomic_compare_and_store64_nosync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t cvmx_atomic_compare_and_store64(uint64_t *ptr, uint64_t old_val, uint64_t new_val)
{
    uint64_t ret;
    CVMX_SYNCWS;
    ret = cvmx_atomic_compare_and_store64_nosync(ptr, old_val, new_val);
    CVMX_SYNCWS;
    return ret;
}