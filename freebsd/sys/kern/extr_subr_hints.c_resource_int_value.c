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
 int EFTYPE ; 
 int resource_find (int*,int /*<<< orphan*/ *,char const*,int*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

int
resource_int_value(const char *name, int unit, const char *resname, int *result)
{
	int error;
	const char *str;
	char *op;
	unsigned long val;
	int line;

	line = 0;
	error = resource_find(&line, NULL, name, &unit, resname, NULL,
	    NULL, NULL, NULL, NULL, NULL, &str);
	if (error)
		return error;
	if (*str == '\0') 
		return EFTYPE;
	val = strtoul(str, &op, 0);
	if (*op != '\0') 
		return EFTYPE;
	*result = val;
	return 0;
}