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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ ARM64_NCAPS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  applied_alternatives ; 
 int test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

bool alternative_is_applied(u16 cpufeature)
{
	if (WARN_ON(cpufeature >= ARM64_NCAPS))
		return false;

	return test_bit(cpufeature, applied_alternatives);
}