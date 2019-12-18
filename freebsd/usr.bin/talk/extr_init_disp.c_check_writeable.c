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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int S_IWGRP ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 

void
check_writeable(void)
{
	char *tty;
	struct stat sb;

	if ((tty = ttyname(STDERR_FILENO)) == NULL)
		err(1, "ttyname");
	if (stat(tty, &sb) < 0)
		err(1, "%s", tty);
	if (!(sb.st_mode & S_IWGRP))
		errx(1, "The callee cannot write to this terminal, use \"mesg y\".");
}