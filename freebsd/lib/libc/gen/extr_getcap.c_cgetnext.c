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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int BSIZE ; 
 int /*<<< orphan*/  cgetclose () ; 
 char** dbp ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getent (char**,int /*<<< orphan*/ *,char**,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gottoprec ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/ * pfp ; 
 int slash ; 
 char* toprec ; 

int
cgetnext(char **bp, char **db_array)
{
	size_t len;
	int done, hadreaderr, savederrno, status;
	char *cp, *line, *rp, *np, buf[BSIZE], nbuf[BSIZE];
	u_int dummy;

	if (dbp == NULL)
		dbp = db_array;

	if (pfp == NULL && (pfp = fopen(*dbp, "re")) == NULL) {
		(void)cgetclose();
		return (-1);
	}
	for (;;) {
		if (toprec && !gottoprec) {
			gottoprec = 1;
			line = toprec;
		} else {
			line = fgetln(pfp, &len);
			if (line == NULL && pfp) {
				hadreaderr = ferror(pfp);
				if (hadreaderr)
					savederrno = errno;
				fclose(pfp);
				pfp = NULL;
				if (hadreaderr) {
					cgetclose();
					errno = savederrno;
					return (-1);
				} else {
					if (*++dbp == NULL) {
						(void)cgetclose();
						return (0);
					} else if ((pfp =
					    fopen(*dbp, "re")) == NULL) {
						(void)cgetclose();
						return (-1);
					} else
						continue;
				}
			} else
				line[len - 1] = '\0';
			if (len == 1) {
				slash = 0;
				continue;
			}
			if (isspace((unsigned char)*line) ||
			    *line == ':' || *line == '#' || slash) {
				if (line[len - 2] == '\\')
					slash = 1;
				else
					slash = 0;
				continue;
			}
			if (line[len - 2] == '\\')
				slash = 1;
			else
				slash = 0;
		}


		/*
		 * Line points to a name line.
		 */
		done = 0;
		np = nbuf;
		for (;;) {
			for (cp = line; *cp != '\0'; cp++) {
				if (*cp == ':') {
					*np++ = ':';
					done = 1;
					break;
				}
				if (*cp == '\\')
					break;
				*np++ = *cp;
			}
			if (done) {
				*np = '\0';
				break;
			} else { /* name field extends beyond the line */
				line = fgetln(pfp, &len);
				if (line == NULL && pfp) {
					/* Name extends beyond the EOF! */
					hadreaderr = ferror(pfp);
					if (hadreaderr)
						savederrno = errno;
					fclose(pfp);
					pfp = NULL;
					if (hadreaderr) {
						cgetclose();
						errno = savederrno;
						return (-1);
					} else {
						cgetclose();
						return (-1);
					}
				} else
					line[len - 1] = '\0';
			}
		}
		rp = buf;
		for(cp = nbuf; *cp != '\0'; cp++)
			if (*cp == '|' || *cp == ':')
				break;
			else
				*rp++ = *cp;

		*rp = '\0';
		/*
		 * XXX
		 * Last argument of getent here should be nbuf if we want true
		 * sequential access in the case of duplicates.
		 * With NULL, getent will return the first entry found
		 * rather than the duplicate entry record.  This is a
		 * matter of semantics that should be resolved.
		 */
		status = getent(bp, &dummy, db_array, -1, buf, 0, NULL);
		if (status == -2 || status == -3)
			(void)cgetclose();

		return (status + 1);
	}
	/* NOTREACHED */
}