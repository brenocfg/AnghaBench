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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_EXIT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,long long,long long) ; 
 int /*<<< orphan*/  sflag ; 

void
diffmsg(const char *file1, const char *file2, off_t byte, off_t line)
{
	if (!sflag)
		(void)printf("%s %s differ: char %lld, line %lld\n",
		    file1, file2, (long long)byte, (long long)line);
	exit(DIFF_EXIT);
}