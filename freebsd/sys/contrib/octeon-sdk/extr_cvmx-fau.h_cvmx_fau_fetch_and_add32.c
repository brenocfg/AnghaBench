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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  cvmx_fau_reg_32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_fau_atomic_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read64_int32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int32_t cvmx_fau_fetch_and_add32(cvmx_fau_reg_32_t reg, int32_t value)
{
    return cvmx_read64_int32(__cvmx_fau_atomic_address(0, reg, value));
}