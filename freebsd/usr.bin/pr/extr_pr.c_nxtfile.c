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
typedef  int time_t ;
struct tm {int dummy; } ;
struct stat {int st_mtime; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  HDBUF ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int eoptind ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  errcnt ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 char* fnamedefault ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 char* header ; 
 struct tm* localtime (int*) ; 
 scalar_t__ nodiag ; 
 scalar_t__ nohead ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strftime (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tm*) ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timefrmt ; 

FILE *
nxtfile(int argc, char **argv, const char **fname, char *buf, int dt)
{
	FILE *inf = NULL;
	time_t tv_sec;
	struct tm *timeptr = NULL;
	struct stat statbuf;
	static int twice = -1;

	++twice;
	if (eoptind >= argc) {
		/*
		 * no file listed; default, use standard input
		 */
		if (twice)
			return(NULL);
		clearerr(stdin);
		inf = stdin;
		if (header != NULL)
			*fname = header;
		else
			*fname = fnamedefault;
		if (nohead)
			return(inf);
		if ((tv_sec = time(NULL)) == -1) {
			++errcnt;
			(void)fprintf(err, "pr: cannot get time of day, %s\n",
				strerror(errno));
			eoptind = argc - 1;
			return(NULL);
		}
		timeptr = localtime(&tv_sec);
	}
	for (; eoptind < argc; ++eoptind) {
		if (strcmp(argv[eoptind], "-") == 0) {
			/*
			 * process a "-" for filename
			 */
			clearerr(stdin);
			inf = stdin;
			if (header != NULL)
				*fname = header;
			else
				*fname = fnamedefault;
			++eoptind;
			if (nohead || (dt && twice))
				return(inf);
			if ((tv_sec = time(NULL)) == -1) {
				++errcnt;
				(void)fprintf(err,
					"pr: cannot get time of day, %s\n",
					strerror(errno));
				return(NULL);
			}
			timeptr = localtime(&tv_sec);
		} else {
			/*
			 * normal file processing
			 */
			if ((inf = fopen(argv[eoptind], "r")) == NULL) {
				++errcnt;
				if (nodiag)
					continue;
				(void)fprintf(err, "pr: cannot open %s, %s\n",
					argv[eoptind], strerror(errno));
				continue;
			}
			if (header != NULL)
				*fname = header;
			else if (dt)
				*fname = fnamedefault;
			else
				*fname = argv[eoptind];
			++eoptind;
			if (nohead || (dt && twice))
				return(inf);

			if (dt) {
				if ((tv_sec = time(NULL)) == -1) {
					++errcnt;
					(void)fprintf(err,
					     "pr: cannot get time of day, %s\n",
					     strerror(errno));
					fclose(inf);
					return(NULL);
				}
				timeptr = localtime(&tv_sec);
			} else {
				if (fstat(fileno(inf), &statbuf) < 0) {
					++errcnt;
					(void)fclose(inf);
					(void)fprintf(err,
						"pr: cannot stat %s, %s\n",
						argv[eoptind], strerror(errno));
					return(NULL);
				}
				timeptr = localtime(&(statbuf.st_mtime));
			}
		}
		break;
	}
	if (inf == NULL)
		return(NULL);

	/*
	 * set up time field used in header
	 */
	if (strftime(buf, HDBUF, timefrmt, timeptr) <= 0) {
		++errcnt;
		if (inf != stdin)
			(void)fclose(inf);
		(void)fputs("pr: time conversion failed\n", err);
		return(NULL);
	}
	return(inf);
}