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
#define  F_LITERAL 136 
#define  F_TCONVERR 135 
#define  F_TERMCAP 134 
#define  F_TERMINFO 133 
#define  F_VARIABLE 132 
#define  S_NOSORT 131 
#define  S_TERMCAP 130 
#define  S_TERMINFO 129 
#define  S_VARIABLE 128 
 int V_AIX ; 
 int V_ALLCAPS ; 
 int V_BSD ; 
 int V_HPUX ; 
 int V_SVR1 ; 
 char* _nc_progname ; 
 int /*<<< orphan*/  bool_indirect ; 
 int /*<<< orphan*/  bool_names ; 
 int /*<<< orphan*/  bool_termcap_sort ; 
 int /*<<< orphan*/  bool_terminfo_sort ; 
 int /*<<< orphan*/  bool_variable_sort ; 
 int /*<<< orphan*/  boolcodes ; 
 int /*<<< orphan*/  boolfnames ; 
 int /*<<< orphan*/  boolnames ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int height ; 
 int /*<<< orphan*/  num_indirect ; 
 int /*<<< orphan*/  num_names ; 
 int /*<<< orphan*/  num_termcap_sort ; 
 int /*<<< orphan*/  num_terminfo_sort ; 
 int /*<<< orphan*/  num_variable_sort ; 
 int /*<<< orphan*/  numcodes ; 
 int /*<<< orphan*/  numfnames ; 
 int /*<<< orphan*/  numnames ; 
 int outform ; 
 int pretty ; 
 char* separator ; 
 int sortmode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  str_indirect ; 
 int /*<<< orphan*/  str_names ; 
 int /*<<< orphan*/  str_termcap_sort ; 
 int /*<<< orphan*/  str_terminfo_sort ; 
 int /*<<< orphan*/  str_variable_sort ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcodes ; 
 int /*<<< orphan*/  strfnames ; 
 int /*<<< orphan*/  strnames ; 
 char* trailer ; 
 int tversion ; 
 int width ; 

void
dump_init(const char *version,
	  int mode,
	  int sort,
	  int twidth,
	  int theight,
	  unsigned traceval,
	  bool formatted)
/* set up for entry display */
{
    width = twidth;
    height = theight;
    pretty = formatted;

    /* versions */
    if (version == 0)
	tversion = V_ALLCAPS;
    else if (!strcmp(version, "SVr1") || !strcmp(version, "SVR1")
	     || !strcmp(version, "Ultrix"))
	tversion = V_SVR1;
    else if (!strcmp(version, "HP"))
	tversion = V_HPUX;
    else if (!strcmp(version, "AIX"))
	tversion = V_AIX;
    else if (!strcmp(version, "BSD"))
	tversion = V_BSD;
    else
	tversion = V_ALLCAPS;

    /* implement display modes */
    switch (outform = mode) {
    case F_LITERAL:
    case F_TERMINFO:
	bool_names = boolnames;
	num_names = numnames;
	str_names = strnames;
	separator = (twidth > 0 && theight > 1) ? ", " : ",";
	trailer = "\n\t";
	break;

    case F_VARIABLE:
	bool_names = boolfnames;
	num_names = numfnames;
	str_names = strfnames;
	separator = (twidth > 0 && theight > 1) ? ", " : ",";
	trailer = "\n\t";
	break;

    case F_TERMCAP:
    case F_TCONVERR:
	bool_names = boolcodes;
	num_names = numcodes;
	str_names = strcodes;
	separator = ":";
	trailer = "\\\n\t:";
	break;
    }

    /* implement sort modes */
    switch (sortmode = sort) {
    case S_NOSORT:
	if (traceval)
	    (void) fprintf(stderr,
			   "%s: sorting by term structure order\n", _nc_progname);
	break;

    case S_TERMINFO:
	if (traceval)
	    (void) fprintf(stderr,
			   "%s: sorting by terminfo name order\n", _nc_progname);
	bool_indirect = bool_terminfo_sort;
	num_indirect = num_terminfo_sort;
	str_indirect = str_terminfo_sort;
	break;

    case S_VARIABLE:
	if (traceval)
	    (void) fprintf(stderr,
			   "%s: sorting by C variable order\n", _nc_progname);
	bool_indirect = bool_variable_sort;
	num_indirect = num_variable_sort;
	str_indirect = str_variable_sort;
	break;

    case S_TERMCAP:
	if (traceval)
	    (void) fprintf(stderr,
			   "%s: sorting by termcap name order\n", _nc_progname);
	bool_indirect = bool_termcap_sort;
	num_indirect = num_termcap_sort;
	str_indirect = str_termcap_sort;
	break;
    }

    if (traceval)
	(void) fprintf(stderr,
		       "%s: width = %d, tversion = %d, outform = %d\n",
		       _nc_progname, width, tversion, outform);
}