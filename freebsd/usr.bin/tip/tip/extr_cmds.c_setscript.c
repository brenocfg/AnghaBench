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
 int /*<<< orphan*/  RECORD ; 
 int /*<<< orphan*/  SCRIPT ; 
 int /*<<< orphan*/  SIGEMT ; 
 scalar_t__ boolean (char*) ; 
 int /*<<< orphan*/ * fildes ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * repdes ; 
 int size (char*) ; 
 int /*<<< orphan*/  tipout_pid ; 
 char* value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

void
setscript(void)
{
	char c;

	/*
	 * enable TIPOUT side for dialogue
	 */
	kill(tipout_pid, SIGEMT);
	if (boolean(value(SCRIPT)))
		write(fildes[1], value(RECORD), size(value(RECORD)));
	write(fildes[1], "\n", 1);
	/*
	 * wait for TIPOUT to finish
	 */
	read(repdes[0], &c, 1);
	if (c == 'n')
		printf("can't create %s\r\n", value(RECORD));
}