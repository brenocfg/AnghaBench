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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  cvmx_fau_tagwait64_t ;
typedef  int /*<<< orphan*/  cvmx_fau_reg_64_t ;

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_fau_atomic_address (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read64_int64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline cvmx_fau_tagwait64_t cvmx_fau_tagwait_fetch_and_add64(cvmx_fau_reg_64_t reg, int64_t value)
{
    union
    {
        uint64_t i64;
        cvmx_fau_tagwait64_t t;
    } result;
    result.i64 = cvmx_read64_int64(__cvmx_fau_atomic_address(1, reg, value));
    return result.t;
}