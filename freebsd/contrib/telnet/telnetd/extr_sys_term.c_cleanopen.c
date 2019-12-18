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
 int O_NOCTTY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  chown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  revoke (char*) ; 

int
cleanopen(char *li)
{
	int t;

	/*
	 * Make sure that other people can't open the
	 * slave side of the connection.
	 */
	(void) chown(li, 0, 0);
	(void) chmod(li, 0600);

	(void) revoke(li);

	t = open(line, O_RDWR|O_NOCTTY);

	if (t < 0)
		return(-1);

	return(t);
}