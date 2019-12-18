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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 scalar_t__ fsize (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 char* getdeadletter () ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int umask (int) ; 

void
savedeadletter(FILE *fp)
{
	FILE *dbuf;
	int c;
	char *cp;

	if (fsize(fp) == 0)
		return;
	cp = getdeadletter();
	c = umask(077);
	dbuf = Fopen(cp, "a");
	(void)umask(c);
	if (dbuf == NULL)
		return;
	while ((c = getc(fp)) != EOF)
		(void)putc(c, dbuf);
	(void)Fclose(dbuf);
	rewind(fp);
}