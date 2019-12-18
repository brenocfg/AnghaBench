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
 int /*<<< orphan*/  setup_test (char*) ; 
 int /*<<< orphan*/  test_simplesignal_impl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_simplestsignal(void)
{
	setup_test("Simplest one signal: ");
	test_simplesignal_impl(0);
}