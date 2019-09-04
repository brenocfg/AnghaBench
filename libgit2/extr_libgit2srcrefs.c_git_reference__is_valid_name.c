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
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_reference__normalize_name (int /*<<< orphan*/ *,char const*,unsigned int) ; 

int git_reference__is_valid_name(const char *refname, unsigned int flags)
{
	if (git_reference__normalize_name(NULL, refname, flags) < 0) {
		git_error_clear();
		return false;
	}

	return true;
}