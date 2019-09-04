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
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_deepen(const char *line, int *depth)
{
	const char *arg;
	if (skip_prefix(line, "deepen ", &arg)) {
		char *end = NULL;
		*depth = (int)strtol(arg, &end, 0);
		if (!end || *end || *depth <= 0)
			die("Invalid deepen: %s", line);
		return 1;
	}

	return 0;
}