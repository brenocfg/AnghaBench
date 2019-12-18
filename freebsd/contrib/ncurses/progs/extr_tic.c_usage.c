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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  ExitProgram (int /*<<< orphan*/ ) ; 
 size_t SIZEOF (char const* const*) ; 
 char* _nc_progname ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fputs (char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* usage_string ; 

__attribute__((used)) static void
usage(void)
{
    static const char *const tbl[] =
    {
	"Options:",
	"  -1         format translation output one capability per line",
#if NCURSES_XNAMES
	"  -a         retain commented-out capabilities (sets -x also)",
#endif
	"  -K         translate entries to termcap source form with BSD syntax",
	"  -C         translate entries to termcap source form",
	"  -D         print list of tic's database locations (first must be writable)",
	"  -c         check only, validate input without compiling or translating",
	"  -e<names>  translate/compile only entries named by comma-separated list",
	"  -f         format complex strings for readability",
	"  -G         format %{number} to %'char'",
	"  -g         format %'char' to %{number}",
	"  -I         translate entries to terminfo source form",
	"  -L         translate entries to full terminfo source form",
	"  -N         disable smart defaults for source translation",
	"  -o<dir>    set output directory for compiled entry writes",
	"  -R<name>   restrict translation to given terminfo/termcap version",
	"  -r         force resolution of all use entries in source translation",
	"  -s         print summary statistics",
	"  -T         remove size-restrictions on compiled description",
#if NCURSES_XNAMES
	"  -t         suppress commented-out capabilities",
#endif
	"  -U         suppress post-processing of entries",
	"  -V         print version",
	"  -v[n]      set verbosity level",
	"  -w[n]      set format width for translation output",
#if NCURSES_XNAMES
	"  -x         treat unknown capabilities as user-defined",
#endif
	"",
	"Parameters:",
	"  <file>     file to translate or compile"
    };
    size_t j;

    fprintf(stderr, "Usage: %s %s\n", _nc_progname, usage_string);
    for (j = 0; j < SIZEOF(tbl); j++) {
	fputs(tbl[j], stderr);
	putc('\n', stderr);
    }
    ExitProgram(EXIT_FAILURE);
}