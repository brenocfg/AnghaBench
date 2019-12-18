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
typedef  int /*<<< orphan*/  ebuf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

char *
strerror(
	int errnum
	)
{
	extern int sys_nerr;
	extern char *sys_errlist[];
	static char ebuf[20];

	if ((unsigned int)errnum < sys_nerr)
		return sys_errlist[errnum];
	snprintf(ebuf, sizeof(ebuf), "Unknown error: %d", errnum);

	return ebuf;
}