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

/* Variables and functions */
 char* decode_events (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  report_state (char const*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
report(int num, const char *state, int expected, int got, int res,
    int res_expected)
{

	if (res != res_expected) {
		printf("not ok %-2d", num);
		report_state(state);
		printf("poll result %d expected %d. ",
		    res, res_expected);
	} else {
		if (expected == got)
			printf("ok %-2d    ", num);
		else
			printf("not ok %-2d", num);
		report_state(state);
	}
	printf("expected %s; got %s\n", decode_events(expected),
	    decode_events(got));
	fflush(stdout);
}