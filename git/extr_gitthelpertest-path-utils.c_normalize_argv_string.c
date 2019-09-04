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
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void normalize_argv_string(const char **var, const char *input)
{
	if (!strcmp(input, "<null>"))
		*var = NULL;
	else if (!strcmp(input, "<empty>"))
		*var = "";
	else
		*var = input;

	if (*var && (**var == '<' || **var == '('))
		die("Bad value: %s\n", input);
}