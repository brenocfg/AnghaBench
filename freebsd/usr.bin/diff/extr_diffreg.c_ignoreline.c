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
 int /*<<< orphan*/ * ignore_pats ; 
 int ignoreline_pattern (char*) ; 

__attribute__((used)) static bool
ignoreline(char *line, bool skip_blanks)
{

	if (ignore_pats != NULL && skip_blanks)
		return (ignoreline_pattern(line) || *line == '\0');
	if (ignore_pats != NULL)
		return (ignoreline_pattern(line));
	if (skip_blanks)
		return (*line == '\0');
	/* No ignore criteria specified */
	return (false);
}