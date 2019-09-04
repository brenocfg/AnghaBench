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
 int DECORATE_FULL_REFS ; 
 int DECORATE_SHORT_REFS ; 
 int auto_decoration_style () ; 
 int git_parse_maybe_bool (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_decoration_style(const char *value)
{
	switch (git_parse_maybe_bool(value)) {
	case 1:
		return DECORATE_SHORT_REFS;
	case 0:
		return 0;
	default:
		break;
	}
	if (!strcmp(value, "full"))
		return DECORATE_FULL_REFS;
	else if (!strcmp(value, "short"))
		return DECORATE_SHORT_REFS;
	else if (!strcmp(value, "auto"))
		return auto_decoration_style();
	/*
	 * Please update _git_log() in git-completion.bash when you
	 * add new decoration styles.
	 */
	return -1;
}