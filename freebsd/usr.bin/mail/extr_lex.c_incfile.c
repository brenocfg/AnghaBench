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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fsize (int /*<<< orphan*/ *) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  holdsigs () ; 
 int /*<<< orphan*/  mailname ; 
 scalar_t__ mailsize ; 
 int msgCount ; 
 int /*<<< orphan*/  relsesigs () ; 
 int /*<<< orphan*/  setmsize (int) ; 
 int /*<<< orphan*/  setptr (int /*<<< orphan*/ *,scalar_t__) ; 

int
incfile(void)
{
	off_t newsize;
	int omsgCount = msgCount;
	FILE *ibuf;

	ibuf = Fopen(mailname, "r");
	if (ibuf == NULL)
		return (-1);
	holdsigs();
	newsize = fsize(ibuf);
	if (newsize == 0)
		return (-1);		/* mail box is now empty??? */
	if (newsize < mailsize)
		return (-1);		/* mail box has shrunk??? */
	if (newsize == mailsize)
		return (0);		/* no new mail */
	setptr(ibuf, mailsize);
	setmsize(msgCount);
	mailsize = ftello(ibuf);
	(void)Fclose(ibuf);
	relsesigs();
	return (msgCount - omsgCount);
}