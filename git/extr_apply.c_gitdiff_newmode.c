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
struct patch {int /*<<< orphan*/  new_mode; } ;
struct gitdiff_data {int /*<<< orphan*/  linenr; } ;

/* Variables and functions */
 int parse_mode_line (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gitdiff_newmode(struct gitdiff_data *state,
			   const char *line,
			   struct patch *patch)
{
	return parse_mode_line(line, state->linenr, &patch->new_mode);
}