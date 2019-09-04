#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ git_time ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int GIT_DATE_RFC2822_SZ ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__date_rfc2822_fmt (char*,int,TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void test_date_rfc2822__format_rfc2822_no_offset(void)
{
	git_time t = {1397031663, 0};
	char buf[GIT_DATE_RFC2822_SZ];

	cl_git_pass(git__date_rfc2822_fmt(buf, sizeof(buf), &t));
	cl_assert(strcmp(buf, "Wed, 9 Apr 2014 08:21:03 +0000") == 0);
}