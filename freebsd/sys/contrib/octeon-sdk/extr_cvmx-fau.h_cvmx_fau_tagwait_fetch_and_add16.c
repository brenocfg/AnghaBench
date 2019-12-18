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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  cvmx_fau_tagwait16_t ;
typedef  int /*<<< orphan*/  cvmx_fau_reg_16_t ;

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_fau_atomic_address (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read64_int16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline cvmx_fau_tagwait16_t cvmx_fau_tagwait_fetch_and_add16(cvmx_fau_reg_16_t reg, int16_t value)
{
    union
    {
        uint64_t i16;
        cvmx_fau_tagwait16_t t;
    } result;
    result.i16 = cvmx_read64_int16(__cvmx_fau_atomic_address(1, reg, value));
    return result.t;
}