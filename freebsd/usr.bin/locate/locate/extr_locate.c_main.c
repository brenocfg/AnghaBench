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
 int /*<<< orphan*/  LC_ALL ; 
 int UCHAR_MAX ; 
 char* _PATH_FCODES ; 
 int /*<<< orphan*/  atoi (char*) ; 
 char** colon (char**,char*,char*) ; 
 int /*<<< orphan*/  counter ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int f_icase ; 
 int /*<<< orphan*/  f_limit ; 
 int f_mmap ; 
 int f_silent ; 
 int f_statistic ; 
 int f_stdin ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * myctype ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_matches (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_fopen (char*,char**) ; 
 int /*<<< orphan*/  search_mmap (char*,char**) ; 
 char separator ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  tolower (int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char **argv)
{
        register int ch;
        char **dbv = NULL;
	char *path_fcodes;      /* locate database */
#ifdef MMAP
        f_mmap = 1;		/* mmap is default */
#endif
	(void) setlocale(LC_ALL, "");

        while ((ch = getopt(argc, argv, "0Scd:il:ms")) != -1)
                switch(ch) {
                case '0':	/* 'find -print0' style */
			separator = '\0';
			break;
                case 'S':	/* statistic lines */   
                        f_statistic = 1;
                        break;
                case 'l': /* limit number of output lines, 0 == infinite */
                        f_limit = atoi(optarg);
                        break;
                case 'd':	/* database */
                        dbv = colon(dbv, optarg, _PATH_FCODES);
                        break;
                case 'i':	/* ignore case */
                        f_icase = 1;
                        break;
                case 'm':	/* mmap */
#ifdef MMAP
                        f_mmap = 1;
#else
						warnx("mmap(2) not implemented");
#endif
                        break;
                case 's':	/* stdio lib */
                        f_mmap = 0;
                        break;
                case 'c': /* suppress output, show only count of matches */
                        f_silent = 1;
                        break;
                default:
                        usage();
                }
        argv += optind;
        argc -= optind;

        /* to few arguments */
        if (argc < 1 && !(f_statistic))
                usage();

        /* no (valid) database as argument */
        if (dbv == NULL || *dbv == NULL) {
                /* try to read database from environment */
                if ((path_fcodes = getenv("LOCATE_PATH")) == NULL ||
		     *path_fcodes == '\0')
                        /* use default database */
                        dbv = colon(dbv, _PATH_FCODES, _PATH_FCODES);
                else		/* $LOCATE_PATH */
                        dbv = colon(dbv, path_fcodes, _PATH_FCODES);
        }

        if (f_icase && UCHAR_MAX < 4096) /* init tolower lookup table */
                for (ch = 0; ch < UCHAR_MAX + 1; ch++)
                        myctype[ch] = tolower(ch);

        /* foreach database ... */
        while((path_fcodes = *dbv) != NULL) {
                dbv++;

                if (!strcmp(path_fcodes, "-"))
                        f_stdin = 1;
		else
			f_stdin = 0;

#ifndef MMAP
		f_mmap = 0;	/* be paranoid */
#endif
                if (!f_mmap || f_stdin || f_statistic) 
			search_fopen(path_fcodes, argv);
                else 
			search_mmap(path_fcodes, argv);
        }

        if (f_silent)
                print_matches(counter);
        exit(0);
}