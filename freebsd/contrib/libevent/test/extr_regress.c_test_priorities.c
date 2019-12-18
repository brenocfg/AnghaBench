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
 scalar_t__ test_ok ; 
 int /*<<< orphan*/  test_priorities_impl (int) ; 

__attribute__((used)) static void
test_priorities(void)
{
	test_priorities_impl(1);
	if (test_ok)
		test_priorities_impl(2);
	if (test_ok)
		test_priorities_impl(3);
}