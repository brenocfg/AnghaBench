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
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  error_buf ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REGEX ; 
 int REG_NOMATCH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_set_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/  const*,char*,int) ; 

int git_error_set_regex(const regex_t *regex, int error_code)
{
	char error_buf[1024];

	assert(error_code);

	regerror(error_code, regex, error_buf, sizeof(error_buf));
	git_error_set_str(GIT_ERROR_REGEX, error_buf);

	if (error_code == REG_NOMATCH)
		return GIT_ENOTFOUND;

	return GIT_EINVALIDSPEC;
}