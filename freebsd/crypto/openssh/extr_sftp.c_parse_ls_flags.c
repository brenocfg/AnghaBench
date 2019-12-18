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
 int LS_LONG_VIEW ; 
 int LS_NAME_SORT ; 
 int LS_NUMERIC_VIEW ; 
 int LS_REVERSE_SORT ; 
 int LS_SHORT_VIEW ; 
 int LS_SHOW_ALL ; 
 int LS_SIZE_SORT ; 
 int LS_SI_UNITS ; 
 int LS_TIME_SORT ; 
 int SORT_FLAGS ; 
 int VIEW_FLAGS ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int getopt (int,char**,char*) ; 

__attribute__((used)) static int
parse_ls_flags(char **argv, int argc, int *lflag)
{
	extern int opterr, optind, optopt, optreset;
	int ch;

	optind = optreset = 1;
	opterr = 0;

	*lflag = LS_NAME_SORT;
	while ((ch = getopt(argc, argv, "1Safhlnrt")) != -1) {
		switch (ch) {
		case '1':
			*lflag &= ~VIEW_FLAGS;
			*lflag |= LS_SHORT_VIEW;
			break;
		case 'S':
			*lflag &= ~SORT_FLAGS;
			*lflag |= LS_SIZE_SORT;
			break;
		case 'a':
			*lflag |= LS_SHOW_ALL;
			break;
		case 'f':
			*lflag &= ~SORT_FLAGS;
			break;
		case 'h':
			*lflag |= LS_SI_UNITS;
			break;
		case 'l':
			*lflag &= ~LS_SHORT_VIEW;
			*lflag |= LS_LONG_VIEW;
			break;
		case 'n':
			*lflag &= ~LS_SHORT_VIEW;
			*lflag |= LS_NUMERIC_VIEW|LS_LONG_VIEW;
			break;
		case 'r':
			*lflag |= LS_REVERSE_SORT;
			break;
		case 't':
			*lflag &= ~SORT_FLAGS;
			*lflag |= LS_TIME_SORT;
			break;
		default:
			error("ls: Invalid flag -%c", optopt);
			return -1;
		}
	}

	return optind;
}