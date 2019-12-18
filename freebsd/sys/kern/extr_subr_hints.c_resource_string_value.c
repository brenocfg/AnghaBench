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
 int resource_find (int*,int /*<<< orphan*/ *,char const*,int*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 

int
resource_string_value(const char *name, int unit, const char *resname,
    const char **result)
{
	int error;
	const char *str;
	int line;

	line = 0;
	error = resource_find(&line, NULL, name, &unit, resname, NULL,
	    NULL, NULL, NULL, NULL, NULL, &str);
	if (error)
		return error;
	*result = str;
	return 0;
}