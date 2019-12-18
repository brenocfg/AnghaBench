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
typedef  int ev_int64_t ;

/* Variables and functions */
 scalar_t__ evutil_strtoll (char const*,char**,int) ; 
 int /*<<< orphan*/  tt_want (int) ; 

__attribute__((used)) static void
test_evutil_strtoll(void *ptr)
{
	const char *s;
	char *endptr;

	tt_want(evutil_strtoll("5000000000", NULL, 10) ==
		((ev_int64_t)5000000)*1000);
	tt_want(evutil_strtoll("-5000000000", NULL, 10) ==
		((ev_int64_t)5000000)*-1000);
	s = " 99999stuff";
	tt_want(evutil_strtoll(s, &endptr, 10) == (ev_int64_t)99999);
	tt_want(endptr == s+6);
	tt_want(evutil_strtoll("foo", NULL, 10) == 0);
 }