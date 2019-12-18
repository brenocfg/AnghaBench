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
typedef  int /*<<< orphan*/  option_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* estrdup (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int set_option_var (int /*<<< orphan*/  const*,char*,char*,char*,size_t) ; 

int
set_option(const option_t *options, const char *option, char *buf, size_t len)
{
	char *var, *val;
	int retval;

	assert(option != NULL);

	var = estrdup(option);
	for (val = var; *val; val++)
		if (*val == '=') {
			*val++ = '\0';
			break;
		}
	retval = set_option_var(options, var, val, buf, len);
	free(var);
	return retval;
}