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
 int /*<<< orphan*/  LCCDIR ; 
 int /*<<< orphan*/  LCCINPUTS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* tempdir ; 
 int /*<<< orphan*/  xx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void help(void) {
	static char *msgs[] = {
"", " [ option | file ]...\n",
"	except for -l, options are processed left-to-right before files\n",
"	unrecognized options are taken to be linker options\n",
"-A	warn about nonANSI usage; 2nd -A warns more\n",
"-b	emit expression-level profiling code; see bprint(1)\n",
#ifdef sparc
"-Bstatic -Bdynamic	specify static or dynamic libraries\n",
#endif
"-Bdir/	use the compiler named `dir/rcc'\n",
"-c	compile only\n",
"-dn	set switch statement density to `n'\n",
"-Dname -Dname=def	define the preprocessor symbol `name'\n",
"-E	run only the preprocessor on the named C programs and unsuffixed files\n",
"-g	produce symbol table information for debuggers\n",
"-help or -?	print this message\n",
"-Idir	add `dir' to the beginning of the list of #include directories\n",	
"-lx	search library `x'\n",
"-N	do not search the standard directories for #include files\n",
"-n	emit code to check for dereferencing zero pointers\n",
"-O	is ignored\n",
"-o file	leave the output in `file'\n",
"-P	print ANSI-style declarations for globals\n",
"-p -pg	emit profiling code; see prof(1) and gprof(1)\n",
"-S	compile to assembly language\n",
#ifdef linux
"-static	specify static libraries (default is dynamic)\n",
#endif
"-t -tname	emit function tracing calls to printf or to `name'\n",
"-target name	is ignored\n",
"-tempdir=dir	place temporary files in `dir/'", "\n"
"-Uname	undefine the preprocessor symbol `name'\n",
"-v	show commands as they are executed; 2nd -v suppresses execution\n",
"-w	suppress warnings\n",
"-Woarg	specify system-specific `arg'\n",
"-W[pfal]arg	pass `arg' to the preprocessor, compiler, assembler, or linker\n",
	0 };
	int i;
	char *s;

	msgs[0] = progname;
	for (i = 0; msgs[i]; i++) {
		fprintf(stderr, "%s", msgs[i]);
		if (strncmp("-tempdir", msgs[i], 8) == 0 && tempdir)
			fprintf(stderr, "; default=%s", tempdir);
	}
#define xx(v) if ((s = getenv(#v))) fprintf(stderr, #v "=%s\n", s)
	xx(LCCINPUTS);
	xx(LCCDIR);
#undef xx
}