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
 int errno ; 
 int something_failed ; 
 int /*<<< orphan*/  warn (char*,char const*,int,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

void
expect(const char *test, int error, int expected_error, int expected_errno)
{

	if (error == 0) {
		if (expected_error != 0) {
			something_failed = 1;
			warnx("%s: returned 0", test);
		}
	} else {
		if (expected_error == 0) {
			something_failed = 1;
			warn("%s: returned (%d, %d)", test, error, errno);
		} else if (expected_errno != errno) {
			something_failed = 1;
			warn("%s: returned (%d, %d)", test, error, errno);
		}
	}
}