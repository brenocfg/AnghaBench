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
 int CHAR_SPACE ; 
 int DASH_LEN ; 
 int /*<<< orphan*/  TIOCMGET ; 
 int /*<<< orphan*/  TIOCMSET ; 
 int TIOCM_RTS ; 
 int WORD_SPACE ; 
 int cdot_clock ; 
 int dot_clock ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
ttyout(const char *s)
{
	const char *c;
	int duration, on, lflags;

	for (c = s; *c != '\0'; c++) {
		switch (*c) {
		case '.':
			on = 1;
			duration = dot_clock;
			break;
		case '-':
			on = 1;
			duration = dot_clock * DASH_LEN;
			break;
		case ' ':
			on = 0;
			duration = cdot_clock * WORD_SPACE;
			break;
		default:
			on = 0;
			duration = 0;
		}
		if (on) {
			ioctl(line, TIOCMGET, &lflags);
			lflags |= TIOCM_RTS;
			ioctl(line, TIOCMSET, &lflags);
		}
		duration *= 10000;
		if (duration)
			usleep(duration);
		ioctl(line, TIOCMGET, &lflags);
		lflags &= ~TIOCM_RTS;
		ioctl(line, TIOCMSET, &lflags);
		duration = dot_clock * 10000;
		usleep(duration);
	}
	duration = cdot_clock * CHAR_SPACE * 10000;
	usleep(duration);
}