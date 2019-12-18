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
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 unsigned int strtoul (char const*,char**,int) ; 

__attribute__((used)) static int parse_mode_line(const char *line, int linenr, unsigned int *mode)
{
	char *end;
	*mode = strtoul(line, &end, 8);
	if (end == line || !isspace(*end))
		return error(_("invalid mode on line %d: %s"), linenr, line);
	return 0;
}