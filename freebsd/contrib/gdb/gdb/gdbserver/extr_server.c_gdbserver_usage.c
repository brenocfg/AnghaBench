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
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void
gdbserver_usage (void)
{
  error ("Usage:\tgdbserver COMM PROG [ARGS ...]\n"
	 "\tgdbserver COMM --attach PID\n"
	 "\n"
	 "COMM may either be a tty device (for serial debugging), or \n"
	 "HOST:PORT to listen for a TCP connection.\n");
}