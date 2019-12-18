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
struct ttyfd {int /*<<< orphan*/  rfd; } ;
struct termios {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCAL ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 struct termios tio_stdio_orig ; 
 int /*<<< orphan*/  ttyclose ; 
 scalar_t__ uart_stdio ; 

__attribute__((used)) static void
ttyopen(struct ttyfd *tf)
{
	struct termios orig, new;

	tcgetattr(tf->rfd, &orig);
	new = orig;
	cfmakeraw(&new);
	new.c_cflag |= CLOCAL;
	tcsetattr(tf->rfd, TCSANOW, &new);
	if (uart_stdio) {
		tio_stdio_orig = orig;
		atexit(ttyclose);
	}
}