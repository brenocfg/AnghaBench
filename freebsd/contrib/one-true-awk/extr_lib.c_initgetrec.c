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
 int* ARGC ; 
 int /*<<< orphan*/  argno ; 
 char* getargv (int) ; 
 int /*<<< orphan*/  infile ; 
 int /*<<< orphan*/  isclvar (char*) ; 
 int /*<<< orphan*/  lookup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setclvar (char*) ; 
 int /*<<< orphan*/  setsval (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  symtab ; 

void initgetrec(void)
{
	int i;
	char *p;

	for (i = 1; i < *ARGC; i++) {
		p = getargv(i); /* find 1st real filename */
		if (p == NULL || *p == '\0') {  /* deleted or zapped */
			argno++;
			continue;
		}
		if (!isclvar(p)) {
			setsval(lookup("FILENAME", symtab), p);
			return;
		}
		setclvar(p);	/* a commandline assignment before filename */
		argno++;
	}
	infile = stdin;		/* no filenames, so use stdin */
}