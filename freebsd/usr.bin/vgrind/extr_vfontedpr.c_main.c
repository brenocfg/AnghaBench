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
struct stat {int /*<<< orphan*/  st_mtime; } ;

/* Variables and functions */
 int BUFSIZ ; 
 size_t PSMAX ; 
 int _escaped ; 
 scalar_t__ blklevel ; 
 int /*<<< orphan*/ * cgetcap (char*,char*,char) ; 
 int cgetent (char**,char**,char*) ; 
 int cgetustr (char*,char*,char**) ; 
 void* convexp (char*) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 char** defsfile ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int filter ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int idx ; 
 int inchr ; 
 int incomm ; 
 int instr ; 
 void* l_acmbeg ; 
 void* l_acmend ; 
 void* l_blkbeg ; 
 void* l_blkend ; 
 void* l_chrbeg ; 
 void* l_chrend ; 
 void* l_combeg ; 
 void* l_comend ; 
 char l_escape ; 
 char** l_keywds ; 
 void* l_nocom ; 
 int /*<<< orphan*/  l_onecase ; 
 void* l_prcbeg ; 
 void* l_strbeg ; 
 void* l_strend ; 
 int /*<<< orphan*/  l_toplex ; 
 char* language ; 
 scalar_t__ margin ; 
 char* minus ; 
 char* minusn ; 
 int nokeyw ; 
 int pass ; 
 scalar_t__* plstack ; 
 int prccont ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ps (char*) ; 
 size_t psptr ; 
 char** pstack ; 
 int /*<<< orphan*/  putScp (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int
main(int argc, char **argv)
{
    const char *fname = "";
    struct stat stbuf;
    char buf[BUFSIZ];
    char *defs;
    int needbp = 0;

    argc--, argv++;
    do {
	char *cp;
	int i;

	if (argc > 0) {
	    if (!strcmp(argv[0], "-h")) {
		if (argc == 1) {
		    printf("'ds =H\n");
		    argc = 0;
		    goto rest;
		}
		printf("'ds =H %s\n", argv[1]);
		argc--, argv++;
		argc--, argv++;
		if (argc > 0)
		    continue;
		goto rest;
	    }

	    /* act as a filter like eqn */
	    if (!strcmp(argv[0], "-f")) {
		filter = true;
		argv[0] = argv[argc-1];
		argv[argc-1] = minus;
		continue;
	    }

	    /* take input from the standard place */
	    if (!strcmp(argv[0], "-")) {
		argc = 0;
		goto rest;
	    }

	    /* build an index */
	    if (!strcmp(argv[0], "-x")) {
		idx = true;
		argv[0] = minusn;
	    }

	    /* indicate no keywords */
	    if (!strcmp(argv[0], "-n")) {
		nokeyw = true;
		argc--, argv++;
		continue;
	    }

	    /* specify the font size */
	    if (!strncmp(argv[0], "-s", 2)) {
		i = 0;
		cp = argv[0] + 2;
		while (*cp)
		    i = i * 10 + (*cp++ - '0');
		printf("'ps %d\n'vs %d\n", i, i+1);
		argc--, argv++;
		continue;
	    }

	    /* specify the language */
	    if (!strncmp(argv[0], "-l", 2)) {
		language = argv[0]+2;
		argc--, argv++;
		continue;
	    }

	    /* specify the language description file */
	    if (!strncmp(argv[0], "-d", 2)) {
		defsfile[0] = argv[1];
		argc--, argv++;
		argc--, argv++;
		continue;
	    }

	    /* open the file for input */
	    if (freopen(argv[0], "r", stdin) == NULL)
		err(1, "%s", argv[0]);
	    if (idx)
		printf("'ta 4i 4.25i 5.5iR\n'in .5i\n");
	    fname = argv[0];
	    argc--, argv++;
	}
    rest:

	/*
	 *  get the  language definition from the defs file
	 */
	i = cgetent(&defs, defsfile, language);
	if (i == -1) {
	    fprintf (stderr, "no entry for language %s\n", language);
	    exit(0);
	} else  if (i == -2) { fprintf(stderr,
	    "cannot find vgrindefs file %s\n", defsfile[0]);
	    exit(0);
	} else if (i == -3) { fprintf(stderr,
	    "potential reference loop detected in vgrindefs file %s\n",
            defsfile[0]);
	    exit(0);
	}
	if (cgetustr(defs, "kw", &cp) == -1)
	    nokeyw = true;
	else  {
	    char **cpp;

	    cpp = l_keywds;
	    while (*cp) {
		while (*cp == ' ' || *cp =='\t')
		    *cp++ = '\0';
		if (*cp)
		    *cpp++ = cp;
		while (*cp != ' ' && *cp  != '\t' && *cp)
		    cp++;
	    }
	    *cpp = NULL;
	}
	cgetustr(defs, "pb", &cp);
	l_prcbeg = convexp(cp);
	cgetustr(defs, "cb", &cp);
	l_combeg = convexp(cp);
	cgetustr(defs, "ce", &cp);
	l_comend = convexp(cp);
	cgetustr(defs, "ab", &cp);
	l_acmbeg = convexp(cp);
	cgetustr(defs, "ae", &cp);
	l_acmend = convexp(cp);
	cgetustr(defs, "sb", &cp);
	l_strbeg = convexp(cp);
	cgetustr(defs, "se", &cp);
	l_strend = convexp(cp);
	cgetustr(defs, "bb", &cp);
	l_blkbeg = convexp(cp);
	cgetustr(defs, "be", &cp);
	l_blkend = convexp(cp);
	cgetustr(defs, "lb", &cp);
	l_chrbeg = convexp(cp);
	cgetustr(defs, "le", &cp);
	l_chrend = convexp(cp);
	if (cgetustr(defs, "nc", &cp) >= 0)
		l_nocom = convexp(cp);
	l_escape = '\\';
	l_onecase = (cgetcap(defs, "oc", ':') != NULL);
	l_toplex = (cgetcap(defs, "tl", ':') != NULL);

	/* initialize the program */

	incomm = false;
	instr = false;
	inchr = false;
	_escaped = false;
	blklevel = 0;
	for (psptr=0; psptr<PSMAX; psptr++) {
	    pstack[psptr][0] = '\0';
	    plstack[psptr] = 0;
	}
	psptr = -1;
	ps("'-F\n");
	if (!filter) {
	    printf(".ds =F %s\n", fname);
	    ps("'wh 0 vH\n");
	    ps("'wh -1i vF\n");
	}
	if (needbp) {
	    needbp = 0;
	    printf(".()\n");
	    printf(".bp\n");
	}
	if (!filter) {
	    fstat(fileno(stdin), &stbuf);
	    cp = ctime(&stbuf.st_mtime);
	    cp[16] = '\0';
	    cp[24] = '\0';
	    printf(".ds =M %s %s\n", cp+4, cp+20);
	}

	/*
	 *	MAIN LOOP!!!
	 */
	while (fgets(buf, sizeof buf, stdin) != NULL) {
	    if (buf[0] == '\f') {
		printf(".bp\n");
	    }
	    if (buf[0] == '.') {
		printf("%s", buf);
		if (!strncmp (buf+1, "vS", 2))
		    pass = true;
		if (!strncmp (buf+1, "vE", 2))
		    pass = false;
		continue;
	    }
	    prccont = false;
	    if (!filter || pass)
		putScp(buf);
	    else
		printf("%s", buf);
	    if (prccont && (psptr >= 0)) {
		ps("'FC ");
		ps(pstack[psptr]);
		ps("\n");
	    }
#ifdef DEBUG
	    printf ("com %o str %o chr %o ptr %d\n", incomm, instr, inchr, psptr);
#endif
	    margin = 0;
	}
	needbp = 1;
    } while (argc > 0);
    exit(0);
}