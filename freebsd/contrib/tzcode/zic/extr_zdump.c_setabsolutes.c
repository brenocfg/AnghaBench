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
typedef  double time_t ;

/* Variables and functions */
 scalar_t__ DBL_MAX ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ FLT_MAX ; 
 char* _ (char*) ; 
 double absolute_max_time ; 
 double absolute_min_time ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
setabsolutes(void)
{
	if (0.5 == (time_t) 0.5) {
		/*
		** time_t is floating.
		*/
		if (sizeof (time_t) == sizeof (float)) {
			absolute_min_time = (time_t) -FLT_MAX;
			absolute_max_time = (time_t) FLT_MAX;
		} else if (sizeof (time_t) == sizeof (double)) {
			absolute_min_time = (time_t) -DBL_MAX;
			absolute_max_time = (time_t) DBL_MAX;
		} else {
			(void) fprintf(stderr,
_("%s: use of -v on system with floating time_t other than float or double\n"),
				progname);
			exit(EXIT_FAILURE);
		}
	} else if (0 > (time_t) -1) {
		/*
		** time_t is signed.  Assume overflow wraps around.
		*/
		time_t t = 0;
		time_t t1 = 1;

		while (t < t1) {
			t = t1;
			t1 = 2 * t1 + 1;
		}

		absolute_max_time = t;
		t = -t;
		absolute_min_time = t - 1;
		if (t < absolute_min_time)
			absolute_min_time = t;
	} else {
		/*
		** time_t is unsigned.
		*/
		absolute_min_time = 0;
		absolute_max_time = absolute_min_time - 1;
	}
}