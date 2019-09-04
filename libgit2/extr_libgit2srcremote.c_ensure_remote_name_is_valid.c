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
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_remote_is_valid_name (char const*) ; 

__attribute__((used)) static int ensure_remote_name_is_valid(const char *name)
{
	int error = 0;

	if (!git_remote_is_valid_name(name)) {
		git_error_set(
			GIT_ERROR_CONFIG,
			"'%s' is not a valid remote name.", name ? name : "(null)");
		error = GIT_EINVALIDSPEC;
	}

	return error;
}