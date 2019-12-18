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
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  mailname ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ rm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * value (char*) ; 

void
demail(void)
{
	int fd;

	if (value("keep") != NULL || rm(mailname) < 0)
		if ((fd = open(mailname, O_CREAT | O_TRUNC | O_WRONLY, 0600)) >=
		    0)
			(void)close(fd);
}