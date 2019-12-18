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
typedef  int /*<<< orphan*/  nltype ;

/* Variables and functions */
 int ANYDEBUG ; 
 char* A_OUTNAME ; 
 void* Cflag ; 
 void* Eflag ; 
 int /*<<< orphan*/  Elist ; 
 void* FALSE ; 
 void* Fflag ; 
 int /*<<< orphan*/  Flist ; 
 int /*<<< orphan*/  GMONSUM ; 
 void* Kflag ; 
 int Lflag ; 
 void* TRUE ; 
 char* a_outname ; 
 int /*<<< orphan*/  addlist (int /*<<< orphan*/ ,char*) ; 
 void* aflag ; 
 int aout_getnfile (char*,char***) ; 
 int /*<<< orphan*/  asgnsamples () ; 
 int atoi (char*) ; 
 void* bflag ; 
 int cyclethreshold ; 
 int debug ; 
 void* dflag ; 
 int /*<<< orphan*/ ** doarcs () ; 
 int /*<<< orphan*/  dumpsum (int /*<<< orphan*/ ) ; 
 void* eflag ; 
 int elf_getnfile (char*,char***) ; 
 int /*<<< orphan*/  elist ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 void* fflag ; 
 int /*<<< orphan*/  flist ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getpfile (char*) ; 
 char* gmonname ; 
 int hz ; 
 int kernel_getnfile (char*,char***) ; 
 void* kflag ; 
 int /*<<< orphan*/  kfromlist ; 
 int /*<<< orphan*/  ktolist ; 
 int lflag ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  nl ; 
 int /*<<< orphan*/  nname ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printgprof (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printindex () ; 
 int /*<<< orphan*/  printprof () ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlinebuf (int /*<<< orphan*/ ) ; 
 void* sflag ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 void* uflag ; 
 int /*<<< orphan*/  valcmp ; 
 void* zflag ; 

int
main(int argc, char **argv)
{
    char	**sp;
    nltype	**timesortnlp;
    char	**defaultEs;

    --argc;
    argv++;
    debug = 0;
    bflag = TRUE;
    while ( *argv != 0 && **argv == '-' ) {
	(*argv)++;
	switch ( **argv ) {
	case 'a':
	    aflag = TRUE;
	    break;
	case 'b':
	    bflag = FALSE;
	    break;
	case 'C':
	    Cflag = TRUE;
	    cyclethreshold = atoi( *++argv );
	    break;
	case 'd':
	    dflag = TRUE;
	    setlinebuf(stdout);
	    debug |= atoi( *++argv );
	    debug |= ANYDEBUG;
#	    ifdef DEBUG
		printf("[main] debug = %d\n", debug);
#	    else /* not DEBUG */
		printf("gprof: -d ignored\n");
#	    endif /* DEBUG */
	    break;
	case 'E':
	    ++argv;
	    addlist( Elist , *argv );
	    Eflag = TRUE;
	    addlist( elist , *argv );
	    eflag = TRUE;
	    break;
	case 'e':
	    addlist( elist , *++argv );
	    eflag = TRUE;
	    break;
	case 'F':
	    ++argv;
	    addlist( Flist , *argv );
	    Fflag = TRUE;
	    addlist( flist , *argv );
	    fflag = TRUE;
	    break;
	case 'f':
	    addlist( flist , *++argv );
	    fflag = TRUE;
	    break;
	case 'k':
	    addlist( kfromlist , *++argv );
	    addlist( ktolist , *++argv );
	    kflag = TRUE;
	    break;
	case 'K':
	    Kflag = TRUE;
	    break;
	case 'l':
	    lflag = 1;
	    Lflag = 0;
	    break;
	case 'L':
	    Lflag = 1;
	    lflag = 0;
	    break;
	case 's':
	    sflag = TRUE;
	    break;
	case 'u':
	    uflag = TRUE;
	    break;
	case 'z':
	    zflag = TRUE;
	    break;
	}
	argv++;
    }
    if ( *argv != 0 ) {
	a_outname  = *argv;
	argv++;
    } else {
	a_outname  = A_OUTNAME;
    }
    if ( *argv != 0 ) {
	gmonname = *argv;
	argv++;
    } else {
	gmonname = (char *) malloc(strlen(a_outname)+6);
	strcpy(gmonname, a_outname);
	strcat(gmonname, ".gmon");
    }
	/*
	 *	get information from the executable file.
	 */
    if ((Kflag && kernel_getnfile(a_outname, &defaultEs) == -1) ||
      (!Kflag && elf_getnfile(a_outname, &defaultEs) == -1
#ifdef WITH_AOUT
      && aout_getnfile(a_outname, &defaultEs) == -1
#endif
      ))
	errx(1, "%s: bad format", a_outname);
	/*
	 *	sort symbol table.
	 */
    qsort(nl, nname, sizeof(nltype), valcmp);
	/*
	 *	turn off default functions
	 */
    for ( sp = defaultEs ; *sp ; sp++ ) {
	Eflag = TRUE;
	addlist( Elist , *sp );
	eflag = TRUE;
	addlist( elist , *sp );
    }
	/*
	 *	get information about mon.out file(s).
	 */
    do	{
	getpfile( gmonname );
	if ( *argv != 0 ) {
	    gmonname = *argv;
	}
    } while ( *argv++ != 0 );
	/*
	 *	how many ticks per second?
	 *	if we can't tell, report time in ticks.
	 */
    if (hz == 0) {
	hz = 1;
	fprintf(stderr, "time is in ticks, not seconds\n");
    }
	/*
	 *	dump out a gmon.sum file if requested
	 */
    if ( sflag ) {
	dumpsum( GMONSUM );
    }
	/*
	 *	assign samples to procedures
	 */
    asgnsamples();
	/*
	 *	assemble the dynamic profile
	 */
    timesortnlp = doarcs();
	/*
	 *	print the dynamic profile
	 */
    if(!lflag) {
	    printgprof( timesortnlp );
    }
	/*
	 *	print the flat profile
	 */
    if(!Lflag) {
	    printprof();
    }
	/*
	 *	print the index
	 */
    printindex();
    exit(0);
}