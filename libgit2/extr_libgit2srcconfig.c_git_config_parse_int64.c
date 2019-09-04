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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 scalar_t__ git__strntol64 (int*,char const*,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_config_parse_int64(int64_t *out, const char *value)
{
	const char *num_end;
	int64_t num;

	if (!value || git__strntol64(&num, value, strlen(value), &num_end, 0) < 0)
		goto fail_parse;

	switch (*num_end) {
	case 'g':
	case 'G':
		num *= 1024;
		/* fallthrough */

	case 'm':
	case 'M':
		num *= 1024;
		/* fallthrough */

	case 'k':
	case 'K':
		num *= 1024;

		/* check that that there are no more characters after the
		 * given modifier suffix */
		if (num_end[1] != '\0')
			return -1;

		/* fallthrough */

	case '\0':
		*out = num;
		return 0;

	default:
		goto fail_parse;
	}

fail_parse:
	git_error_set(GIT_ERROR_CONFIG, "failed to parse '%s' as an integer", value ? value : "(null)");
	return -1;
}