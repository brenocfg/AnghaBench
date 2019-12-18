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
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int errno ; 
 int interrupted ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
cmd_interrupt(int signo)
{
	const char msg[] = "\rInterrupt  \n";
	int olderrno = errno;

	(void)write(STDERR_FILENO, msg, sizeof(msg) - 1);
	interrupted = 1;
	errno = olderrno;
}