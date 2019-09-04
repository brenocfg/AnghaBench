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
 int /*<<< orphan*/  BITFLIP_FILTER_PRIORITY ; 
 int /*<<< orphan*/  GIT_FILTER_DRIVER_PRIORITY ; 
 int /*<<< orphan*/  REVERSE_FILTER_PRIORITY ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_bitflip_filter () ; 
 int /*<<< orphan*/  create_erroneous_filter (char*) ; 
 int /*<<< orphan*/  create_reverse_filter (char*) ; 
 int /*<<< orphan*/  git_filter_register (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void register_custom_filters(void)
{
	static int filters_registered = 0;

	if (!filters_registered) {
		cl_git_pass(git_filter_register(
			"bitflip", create_bitflip_filter(), BITFLIP_FILTER_PRIORITY));

		cl_git_pass(git_filter_register(
			"reverse", create_reverse_filter("+reverse"),
			REVERSE_FILTER_PRIORITY));

		/* re-register reverse filter with standard filter=xyz priority */
		cl_git_pass(git_filter_register(
			"pre-reverse",
			create_reverse_filter("+prereverse"),
			GIT_FILTER_DRIVER_PRIORITY));

		cl_git_pass(git_filter_register(
			"erroneous",
			create_erroneous_filter("+erroneous"),
			GIT_FILTER_DRIVER_PRIORITY));

		filters_registered = 1;
	}
}