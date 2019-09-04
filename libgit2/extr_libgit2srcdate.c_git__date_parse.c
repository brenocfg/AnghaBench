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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  git_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  approxidate_str (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  parse_date_basic (char const*,int /*<<< orphan*/ *,int*) ; 
 int time (int /*<<< orphan*/ *) ; 

int git__date_parse(git_time_t *out, const char *date)
{
	time_t time_sec;
	git_time_t timestamp;
	int offset, error_ret=0;

	if (!parse_date_basic(date, &timestamp, &offset)) {
		*out = timestamp;
		return 0;
	}

	if (time(&time_sec) == -1)
		return -1;

	*out = approxidate_str(date, time_sec, &error_ret);
   return error_ret;
}