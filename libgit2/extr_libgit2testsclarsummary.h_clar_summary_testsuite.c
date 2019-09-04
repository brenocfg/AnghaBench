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
struct tm {int dummy; } ;
struct clar_summary {int /*<<< orphan*/  fp; } ;
typedef  int /*<<< orphan*/  iso_dt ;

/* Variables and functions */
 int fprintf (int /*<<< orphan*/ ,char*,int,char const*,char const*,char*,double,int,int,int) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ strftime (char*,int,char*,struct tm*) ; 

int clar_summary_testsuite(struct clar_summary *summary,
    int idn, const char *name, const char *pkg, time_t timestamp,
    double elapsed, int test_count, int fail_count, int error_count)
{
	struct tm *tm = localtime(&timestamp);
	char iso_dt[20];

	if (strftime(iso_dt, sizeof(iso_dt), "%Y-%m-%dT%H:%M:%S", tm) == 0)
		return -1;

	return fprintf(summary->fp, "\t<testsuite "
		       " id=\"%d\""
		       " name=\"%s\""
		       " package=\"%s\""
		       " hostname=\"localhost\""
		       " timestamp=\"%s\""
		       " time=\"%.2f\""
		       " tests=\"%d\""
		       " failures=\"%d\""
		       " errors=\"%d\">\n",
		       idn, name, pkg, iso_dt, elapsed, test_count, fail_count, error_count);
}