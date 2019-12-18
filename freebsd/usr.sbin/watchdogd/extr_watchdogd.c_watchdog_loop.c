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
struct timespec {int dummy; } ;
struct stat {int dummy; } ;

/* Variables and functions */
 int WD_ACTIVE ; 
 int end_program ; 
 long nap ; 
 int /*<<< orphan*/  sleep (long) ; 
 int stat (char*,struct stat*) ; 
 int system (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_cmd ; 
 int timeout ; 
 int /*<<< orphan*/  warnx (char*) ; 
 long watchdog_check_dogfunction_time (struct timespec*,struct timespec*) ; 
 int watchdog_getuptime (struct timespec*) ; 
 scalar_t__ watchdog_onoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_patpat (int) ; 

__attribute__((used)) static void
watchdog_loop(void)
{
	struct timespec ts_start, ts_end;
	struct stat sb;
	long waited;
	int error, failed;

	while (end_program != 2) {
		failed = 0;

		error = watchdog_getuptime(&ts_start);
		if (error) {
			end_program = 1;
			goto try_end;
		}

		if (test_cmd != NULL)
			failed = system(test_cmd);
		else
			failed = stat("/etc", &sb);

		error = watchdog_getuptime(&ts_end);
		if (error) {
			end_program = 1;
			goto try_end;
		}

		if (failed == 0)
			watchdog_patpat(timeout|WD_ACTIVE);

		waited = watchdog_check_dogfunction_time(&ts_start, &ts_end);
		if (nap - waited > 0)
			sleep(nap - waited);

try_end:
		if (end_program != 0) {
			if (watchdog_onoff(0) == 0) {
				end_program = 2;
			} else {
				warnx("Could not stop the watchdog, not exiting");
				end_program = 0;
			}
		}
	}
}