#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char uschar ;
struct TYPE_7__ {char* sval; int tval; int /*<<< orphan*/  fval; } ;
struct TYPE_6__ {int fval; } ;

/* Variables and functions */
 scalar_t__* ARGC ; 
 int DONTFREE ; 
 int /*<<< orphan*/  FATAL (char*,char*) ; 
 char** FILENAME ; 
 int /*<<< orphan*/ * FS ; 
 int NUM ; 
 int REC ; 
 int /*<<< orphan*/ * RS ; 
 int STR ; 
 scalar_t__ argno ; 
 int /*<<< orphan*/  atof (char*) ; 
 scalar_t__ donefld ; 
 int donerec ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* file ; 
 scalar_t__ firsttime ; 
 TYPE_3__** fldtab ; 
 TYPE_1__* fnrloc ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ freeable (TYPE_3__*) ; 
 char* getargv (scalar_t__) ; 
 int /*<<< orphan*/ * infile ; 
 int /*<<< orphan*/  initgetrec () ; 
 scalar_t__ is_number (char*) ; 
 scalar_t__ isclvar (char*) ; 
 TYPE_1__* nrloc ; 
 int readrec (char**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setclvar (char*) ; 
 int /*<<< orphan*/  setfval (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  xfree (char*) ; 

int getrec(char **pbuf, int *pbufsize, int isrecord)	/* get next input record */
{			/* note: cares whether buf == record */
	int c;
	char *buf = *pbuf;
	uschar saveb0;
	int bufsize = *pbufsize, savebufsize = bufsize;

	if (firsttime) {
		firsttime = 0;
		initgetrec();
	}
	   dprintf( ("RS=<%s>, FS=<%s>, ARGC=%g, FILENAME=%s\n",
		*RS, *FS, *ARGC, *FILENAME) );
	if (isrecord) {
		donefld = 0;
		donerec = 1;
	}
	saveb0 = buf[0];
	buf[0] = 0;
	while (argno < *ARGC || infile == stdin) {
		   dprintf( ("argno=%d, file=|%s|\n", argno, file) );
		if (infile == NULL) {	/* have to open a new file */
			file = getargv(argno);
			if (file == NULL || *file == '\0') {	/* deleted or zapped */
				argno++;
				continue;
			}
			if (isclvar(file)) {	/* a var=value arg */
				setclvar(file);
				argno++;
				continue;
			}
			*FILENAME = file;
			   dprintf( ("opening file %s\n", file) );
			if (*file == '-' && *(file+1) == '\0')
				infile = stdin;
			else if ((infile = fopen(file, "r")) == NULL)
				FATAL("can't open file %s", file);
			setfval(fnrloc, 0.0);
		}
		c = readrec(&buf, &bufsize, infile);
		if (c != 0 || buf[0] != '\0') {	/* normal record */
			if (isrecord) {
				if (freeable(fldtab[0]))
					xfree(fldtab[0]->sval);
				fldtab[0]->sval = buf;	/* buf == record */
				fldtab[0]->tval = REC | STR | DONTFREE;
				if (is_number(fldtab[0]->sval)) {
					fldtab[0]->fval = atof(fldtab[0]->sval);
					fldtab[0]->tval |= NUM;
				}
			}
			setfval(nrloc, nrloc->fval+1);
			setfval(fnrloc, fnrloc->fval+1);
			*pbuf = buf;
			*pbufsize = bufsize;
			return 1;
		}
		/* EOF arrived on this file; set up next */
		if (infile != stdin)
			fclose(infile);
		infile = NULL;
		argno++;
	}
	buf[0] = saveb0;
	*pbuf = buf;
	*pbufsize = savebufsize;
	return 0;	/* true end of file */
}