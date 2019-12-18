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
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  enosys () ; 
 scalar_t__ errno ; 
 int rctl_remove_rule (char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
remove_rule(const char *filter, const char *unexpanded_rule)
{
	int error;

	error = rctl_remove_rule(filter, strlen(filter) + 1, NULL, 0);
	if (error != 0) {
		if (errno == ENOSYS)
			enosys();
		warn("failed to remove rule '%s'", unexpanded_rule);
	}

	return (error);
}