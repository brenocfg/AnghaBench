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
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  CMDLINE ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ STDIN_FILENO ; 
 size_t col ; 
 int /*<<< orphan*/  command (char*) ; 
 int delay ; 
 int /*<<< orphan*/  display () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getch () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ keyboard_dispatch (int) ; 
 char* line ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh () ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int
keyboard(void)
{
	int ch, n;
	struct timeval last, intvl, now, tm;
	fd_set rfds;

	/* Set initial timings */
	gettimeofday(&last, NULL);
	intvl.tv_sec = delay / 1000000;
	intvl.tv_usec = delay % 1000000;
	for (;;) {
		col = 0;
		move(CMDLINE, 0);
		for (;;) {
			/* Determine interval to sleep */
			(void)gettimeofday(&now, NULL);
			tm.tv_sec = last.tv_sec + intvl.tv_sec - now.tv_sec;
			tm.tv_usec = last.tv_usec + intvl.tv_usec - now.tv_usec;
			while (tm.tv_usec < 0) {
				tm.tv_usec += 1000000;
				tm.tv_sec--;
			}
			while (tm.tv_usec >= 1000000) {
				tm.tv_usec -= 1000000;
				tm.tv_sec++;
			}
			if (tm.tv_sec < 0) {
				/* We have to update screen immediately */
				display();
				gettimeofday(&last, NULL);
				continue;
			}

			/* Prepare select  */
			FD_ZERO(&rfds);
			FD_SET(STDIN_FILENO, &rfds);
			n = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tm);

			if (n > 0) {
				/* Read event on stdin */
				ch = getch();

				if (keyboard_dispatch(ch) == 0) {
					refresh();
					continue;
				}
	
				line[col] = '\0';
				command(line + 1);
				/* Refresh delay */
				intvl.tv_sec = delay / 1000000;
				intvl.tv_usec = delay % 1000000;
				refresh();
				break;
			}

			if (n < 0 && errno != EINTR)
				exit(1);

			/* Timeout or signal. Call display another time */
			display();
			gettimeofday(&last, NULL);
		}
	}
}