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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCRIPT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fildes ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * fscript ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * repdes ; 
 int /*<<< orphan*/  setboolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigbuf ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
intEMT(int signo)
{
	char c, line[256];
	char *pline = line;
	char reply;

	read(fildes[0], &c, 1);
	while (c != '\n' && (size_t)(pline - line) < sizeof(line)) {
		*pline++ = c;
		read(fildes[0], &c, 1);
	}
	*pline = '\0';
	if (boolean(value(SCRIPT)) && fscript != NULL)
		fclose(fscript);
	if (pline == line) {
		setboolean(value(SCRIPT), FALSE);
		reply = 'y';
	} else {
		if ((fscript = fopen(line, "a")) == NULL)
			reply = 'n';
		else {
			reply = 'y';
			setboolean(value(SCRIPT), TRUE);
		}
	}
	write(repdes[1], &reply, 1);
	longjmp(sigbuf, 1);
}