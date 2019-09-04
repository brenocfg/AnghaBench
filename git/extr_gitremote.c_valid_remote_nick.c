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
 scalar_t__ is_dir_sep (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dot_or_dotdot (char const*) ; 

__attribute__((used)) static int valid_remote_nick(const char *name)
{
	if (!name[0] || is_dot_or_dotdot(name))
		return 0;

	/* remote nicknames cannot contain slashes */
	while (*name)
		if (is_dir_sep(*name++))
			return 0;
	return 1;
}