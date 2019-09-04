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
 int /*<<< orphan*/  Eflag ; 
 int /*<<< orphan*/  Sflag ; 
 int /*<<< orphan*/  alist ; 
 int /*<<< orphan*/  append (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as ; 
 int /*<<< orphan*/  av ; 
 char* basename (char*) ; 
 int callsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cflag ; 
 int compile (char*,char*) ; 
 int /*<<< orphan*/  compose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* concat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp ; 
 int /*<<< orphan*/  errcnt ; 
 int /*<<< orphan*/  find (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * llist ; 
 char* outfile ; 
 int /*<<< orphan*/  plist ; 
 int suffix (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * suffixes ; 
 char* tempname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filename(char *name, char *base) {
	int status = 0;
	static char *stemp, *itemp;

	if (base == 0)
		base = basename(name);
	switch (suffix(name, suffixes, 4)) {
	case 0:	/* C source files */
		compose(cpp, plist, append(name, 0), 0);
		if (Eflag) {
			status = callsys(av);
			break;
		}
		if (itemp == NULL)
			itemp = tempname(first(suffixes[1]));
		compose(cpp, plist, append(name, 0), append(itemp, 0));
		status = callsys(av);
		if (status == 0)
			return filename(itemp, base);
		break;
	case 1:	/* preprocessed source files */
		if (Eflag)
			break;
		if (Sflag)
			status = compile(name, outfile ? outfile : concat(base, first(suffixes[2])));
		else if ((status = compile(name, stemp?stemp:(stemp=tempname(first(suffixes[2]))))) == 0)
			return filename(stemp, base);
		break;
	case 2:	/* assembly language files */
		if (Eflag)
			break;
		if (!Sflag) {
			char *ofile;
			if (cflag && outfile)
				ofile = outfile;
			else if (cflag)
				ofile = concat(base, first(suffixes[3]));
			else
				ofile = tempname(first(suffixes[3]));
			compose(as, alist, append(name, 0), append(ofile, 0));
			status = callsys(av);
			if (!find(ofile, llist[1]))
				llist[1] = append(ofile, llist[1]);
		}
		break;
	case 3:	/* object files */
		if (!find(name, llist[1]))
			llist[1] = append(name, llist[1]);
		break;
	default:
		if (Eflag) {
			compose(cpp, plist, append(name, 0), 0);
			status = callsys(av);
		}
		llist[1] = append(name, llist[1]);
		break;
	}
	if (status)
		errcnt++;
	return status;
}