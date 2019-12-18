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
typedef  enum presence_check { ____Placeholder_presence_check } presence_check ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 int /*<<< orphan*/  assert (int) ; 
#define  both_checks 130 
 int k_helper_is_present_stat () ; 
 int k_helper_is_present_sysctl () ; 
#define  stat_check 129 
#define  sysctl_check 128 

__attribute__((used)) static bool
k_helper_is_present(enum presence_check how)
{
	bool found;

	switch (how) {
	case both_checks:
		found = k_helper_is_present_stat();
		ATF_CHECK(k_helper_is_present_sysctl() == found);
		break;

	case stat_check:
		found = k_helper_is_present_stat();
		break;

	case sysctl_check:
		found = k_helper_is_present_sysctl();
		break;

	default:
		found = false;
		assert(found);
	}

	return found;
}