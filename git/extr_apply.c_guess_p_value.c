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
struct apply_state {int /*<<< orphan*/  prefix; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int count_slashes (int /*<<< orphan*/ ) ; 
 char* find_name_traditional (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_dev_null (char const*) ; 
 scalar_t__ starts_with (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int guess_p_value(struct apply_state *state, const char *nameline)
{
	char *name, *cp;
	int val = -1;

	if (is_dev_null(nameline))
		return -1;
	name = find_name_traditional(&state->root, nameline, NULL, 0);
	if (!name)
		return -1;
	cp = strchr(name, '/');
	if (!cp)
		val = 0;
	else if (state->prefix) {
		/*
		 * Does it begin with "a/$our-prefix" and such?  Then this is
		 * very likely to apply to our directory.
		 */
		if (starts_with(name, state->prefix))
			val = count_slashes(state->prefix);
		else {
			cp++;
			if (starts_with(cp, state->prefix))
				val = count_slashes(state->prefix) + 1;
		}
	}
	free(name);
	return val;
}