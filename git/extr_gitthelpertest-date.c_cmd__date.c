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
typedef  int /*<<< orphan*/  timestamp_t ;
typedef  int /*<<< orphan*/  time_t ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getnanos (char const**) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_approx_timestamp (char const**,struct timeval*) ; 
 int /*<<< orphan*/  parse_approxidate (char const**,struct timeval*) ; 
 int /*<<< orphan*/  parse_dates (char const**) ; 
 int /*<<< orphan*/  show_dates (char const**,char const*) ; 
 int /*<<< orphan*/  show_human_dates (char const**) ; 
 int /*<<< orphan*/  show_relative_dates (char const**,struct timeval*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_msg ; 

int cmd__date(int argc, const char **argv)
{
	struct timeval now;
	const char *x;

	x = getenv("GIT_TEST_DATE_NOW");
	if (x) {
		now.tv_sec = atoi(x);
		now.tv_usec = 0;
	}
	else
		gettimeofday(&now, NULL);

	argv++;
	if (!*argv)
		usage(usage_msg);
	if (!strcmp(*argv, "relative"))
		show_relative_dates(argv+1, &now);
	else if (!strcmp(*argv, "human"))
		show_human_dates(argv+1);
	else if (skip_prefix(*argv, "show:", &x))
		show_dates(argv+1, x);
	else if (!strcmp(*argv, "parse"))
		parse_dates(argv+1);
	else if (!strcmp(*argv, "approxidate"))
		parse_approxidate(argv+1, &now);
	else if (!strcmp(*argv, "timestamp"))
		parse_approx_timestamp(argv+1, &now);
	else if (!strcmp(*argv, "getnanos"))
		getnanos(argv+1);
	else if (!strcmp(*argv, "is64bit"))
		return sizeof(timestamp_t) == 8 ? 0 : 1;
	else if (!strcmp(*argv, "time_t-is64bit"))
		return sizeof(time_t) == 8 ? 0 : 1;
	else
		usage(usage_msg);
	return 0;
}