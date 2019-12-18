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
struct archive_match {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int set_timefilter (struct archive_match*,int,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,long) ; 
 int validate_time_flag (struct archive*,int,char*) ; 

int
archive_match_include_time(struct archive *_a, int flag, time_t sec,
    long nsec)
{
	int r;

	r = validate_time_flag(_a, flag, "archive_match_include_time");
	if (r != ARCHIVE_OK)
		return (r);
	return set_timefilter((struct archive_match *)_a, flag,
			sec, nsec, sec, nsec);
}