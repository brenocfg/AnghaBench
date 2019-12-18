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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  stderr ; 
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static int
parse_interval(const char *arg, int *j, int *k)
{
	const char *scan = arg;
	char *rest;

	*j = 0;
	*k = -1;
	if (*scan == '-') {
		scan++;
		goto get_k;
	}
	if (!isdigit(*scan))
		goto err;
	*k = strtol(scan, &rest, 10);
	*j = *k - 1;
	scan = rest;
	if (*scan == '-') {
		*k = -1;
		scan++;
	}
get_k:
	if (*scan == '\0')
		return 0;
	if (!isdigit(*scan))
		goto err;
	*k = strtol(scan, &rest, 10);
	scan = rest;
	if (!(*scan == '\0'))
		goto err;

	return 0;

err:
	fprintf(stderr, "syntax error in '%s', must be num[-[num]] or -[num]\n", arg);
	return -1;
}