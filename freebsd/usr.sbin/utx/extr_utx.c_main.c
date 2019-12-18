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
 int /*<<< orphan*/  BOOT_TIME ; 
 int /*<<< orphan*/  SHUTDOWN_TIME ; 
 int boot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int rm (char**) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int
main(int argc, char *argv[])
{

	if (argc == 2 && strcmp(argv[1], "boot") == 0)
		return (boot(BOOT_TIME));
	else if (argc == 2 && strcmp(argv[1], "shutdown") == 0)
		return (boot(SHUTDOWN_TIME));
	else if (argc >= 3 && strcmp(argv[1], "rm") == 0)
		return (rm(&argv[2]));

	fprintf(stderr,
	    "usage: utx boot\n"
	    "       utx shutdown\n"
	    "       utx rm identifier ...\n");
	exit(1);
}