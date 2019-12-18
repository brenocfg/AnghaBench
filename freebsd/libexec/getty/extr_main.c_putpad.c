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
typedef  int speed_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PC ; 
 int cfgetospeed (int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  putchr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 int /*<<< orphan*/  tmode ; 

__attribute__((used)) static void
putpad(const char *s)
{
	int pad = 0;
	speed_t ospeed = cfgetospeed(&tmode);

	if (isdigit(*s)) {
		while (isdigit(*s)) {
			pad *= 10;
			pad += *s++ - '0';
		}
		pad *= 10;
		if (*s == '.' && isdigit(s[1])) {
			pad += s[1] - '0';
			s += 2;
		}
	}

	puts(s);
	/*
	 * If no delay needed, or output speed is
	 * not comprehensible, then don't try to delay.
	 */
	if (pad == 0 || ospeed <= 0)
		return;

	/*
	 * Round up by a half a character frame, and then do the delay.
	 * Too bad there are no user program accessible programmed delays.
	 * Transmitting pad characters slows many terminals down and also
	 * loads the system.
	 */
	pad = (pad * ospeed + 50000) / 100000;
	while (pad--)
		putchr(*PC);
}