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
 int column_config (char const*,char const*,char const*,unsigned int*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

int git_column_config(const char *var, const char *value,
		      const char *command, unsigned int *colopts)
{
	const char *it;

	if (!skip_prefix(var, "column.", &it))
		return 0;

	if (!strcmp(it, "ui"))
		return column_config(var, value, "ui", colopts);

	if (command && !strcmp(it, command))
		return column_config(var, value, it, colopts);

	return 0;
}