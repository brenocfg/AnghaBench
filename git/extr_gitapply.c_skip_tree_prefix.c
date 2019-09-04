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
struct apply_state {int p_value; } ;

/* Variables and functions */

__attribute__((used)) static const char *skip_tree_prefix(struct apply_state *state,
				    const char *line,
				    int llen)
{
	int nslash;
	int i;

	if (!state->p_value)
		return (llen && line[0] == '/') ? NULL : line;

	nslash = state->p_value;
	for (i = 0; i < llen; i++) {
		int ch = line[i];
		if (ch == '/' && --nslash <= 0)
			return (i == 0) ? NULL : &line[i + 1];
	}
	return NULL;
}