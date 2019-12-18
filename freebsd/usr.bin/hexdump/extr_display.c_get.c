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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 scalar_t__ ALL ; 
 scalar_t__ DUP ; 
 scalar_t__ FIRST ; 
 int MIN (int,int) ; 
 scalar_t__ WAIT ; 
 int /*<<< orphan*/ * _argv ; 
 scalar_t__ address ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int blocksize ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 scalar_t__ eaddress ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int length ; 
 int /*<<< orphan*/  next (char**) ; 
 scalar_t__ odmode ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ skip ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

u_char *
get(void)
{
	static int ateof = 1;
	static u_char *curp, *savp;
	int n;
	int need, nread;
	int valid_save = 0;
	u_char *tmpp;

	if (!curp) {
		if ((curp = calloc(1, blocksize)) == NULL)
			err(1, NULL);
		if ((savp = calloc(1, blocksize)) == NULL)
			err(1, NULL);
	} else {
		tmpp = curp;
		curp = savp;
		savp = tmpp;
		address += blocksize;
		valid_save = 1;
	}
	for (need = blocksize, nread = 0;;) {
		/*
		 * if read the right number of bytes, or at EOF for one file,
		 * and no other files are available, zero-pad the rest of the
		 * block and set the end flag.
		 */
		if (!length || (ateof && !next((char **)NULL))) {
			if (odmode && address < skip)
				errx(1, "cannot skip past end of input");
			if (need == blocksize)
				return((u_char *)NULL);
			/*
			 * XXX bcmp() is not quite right in the presence
			 * of multibyte characters.
			 */
			if (vflag != ALL && 
			    valid_save && 
			    bcmp(curp, savp, nread) == 0) {
				if (vflag != DUP)
					(void)printf("*\n");
				return((u_char *)NULL);
			}
			bzero((char *)curp + nread, need);
			eaddress = address + nread;
			return(curp);
		}
		n = fread((char *)curp + nread, sizeof(u_char),
		    length == -1 ? need : MIN(length, need), stdin);
		if (!n) {
			if (ferror(stdin))
				warn("%s", _argv[-1]);
			ateof = 1;
			continue;
		}
		ateof = 0;
		if (length != -1)
			length -= n;
		if (!(need -= n)) {
			/*
			 * XXX bcmp() is not quite right in the presence
			 * of multibyte characters.
			 */
			if (vflag == ALL || vflag == FIRST ||
			    valid_save == 0 ||
			    bcmp(curp, savp, blocksize) != 0) {
				if (vflag == DUP || vflag == FIRST)
					vflag = WAIT;
				return(curp);
			}
			if (vflag == WAIT)
				(void)printf("*\n");
			vflag = DUP;
			address += blocksize;
			need = blocksize;
			nread = 0;
		}
		else
			nread += n;
	}
}