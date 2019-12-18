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
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int git__strntol64 (int*,char const*,size_t,char const**,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int,char const*) ; 

int git__strntol32(int32_t *result, const char *nptr, size_t nptr_len, const char **endptr, int base)
{
	const char *tmp_endptr;
	int32_t tmp_int;
	int64_t tmp_long;
	int error;

	if ((error = git__strntol64(&tmp_long, nptr, nptr_len, &tmp_endptr, base)) < 0)
		return error;

	tmp_int = tmp_long & 0xFFFFFFFF;
	if (tmp_int != tmp_long) {
		int len = (int)(tmp_endptr - nptr);
		git_error_set(GIT_ERROR_INVALID, "failed to convert: '%.*s' is too large", len, nptr);
		return -1;
	}

	*result = tmp_int;
	if (endptr)
		*endptr = tmp_endptr;

	return error;
}