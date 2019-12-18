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
 scalar_t__ EX_USAGE ; 
 char* ErrBuf ; 
 scalar_t__ ExitVal ; 
 scalar_t__ LMTPMode ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
flush_error()
{
	if (LMTPMode)
		printf("%s\r\n", ErrBuf);
	else
	{
		if (ExitVal != EX_USAGE)
			(void) fprintf(stderr, "mail.local: ");
		fprintf(stderr, "%s\n", ErrBuf);
	}
}