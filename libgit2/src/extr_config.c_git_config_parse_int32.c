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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 scalar_t__ git_config_parse_int64 (int*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 

int git_config_parse_int32(int32_t *out, const char *value)
{
	int64_t tmp;
	int32_t truncate;

	if (git_config_parse_int64(&tmp, value) < 0)
		goto fail_parse;

	truncate = tmp & 0xFFFFFFFF;
	if (truncate != tmp)
		goto fail_parse;

	*out = truncate;
	return 0;

fail_parse:
	git_error_set(GIT_ERROR_CONFIG, "failed to parse '%s' as a 32-bit integer", value ? value : "(null)");
	return -1;
}