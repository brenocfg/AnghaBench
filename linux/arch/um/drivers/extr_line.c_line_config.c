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
struct line {int dummy; } ;
struct chan_opts {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int setup_one_line (struct line*,int,char*,struct chan_opts const*,char**) ; 
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

int line_config(struct line *lines, unsigned int num, char *str,
		const struct chan_opts *opts, char **error_out)
{
	char *end;
	int n;

	if (*str == '=') {
		*error_out = "Can't configure all devices from mconsole";
		return -EINVAL;
	}

	n = simple_strtoul(str, &end, 0);
	if (*end++ != '=') {
		*error_out = "Couldn't parse device number";
		return -EINVAL;
	}
	if (n >= num) {
		*error_out = "Device number out of range";
		return -EINVAL;
	}

	return setup_one_line(lines, n, end, opts, error_out);
}