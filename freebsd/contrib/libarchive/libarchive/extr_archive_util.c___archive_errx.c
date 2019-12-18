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
 int /*<<< orphan*/  exit (int) ; 
 int strlen (char const*) ; 
 size_t write (int,char const*,int) ; 

void
__archive_errx(int retvalue, const char *msg)
{
	static const char msg1[] = "Fatal Internal Error in libarchive: ";
	size_t s;

	s = write(2, msg1, strlen(msg1));
	(void)s; /* UNUSED */
	s = write(2, msg, strlen(msg));
	(void)s; /* UNUSED */
	s = write(2, "\n", 1);
	(void)s; /* UNUSED */
	exit(retvalue);
}