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
struct apply_state {int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* prefix_filename (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void prefix_one(struct apply_state *state, char **name)
{
	char *old_name = *name;
	if (!old_name)
		return;
	*name = prefix_filename(state->prefix, *name);
	free(old_name);
}