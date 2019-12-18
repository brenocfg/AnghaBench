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
 size_t SIZEOF (char const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
    static const char *tbl[] =
    {
	"Usage: infocmp [options] [-A directory] [-B directory] [termname...]"
	,""
	,"Options:"
	,"  -0    print single-row"
	,"  -1    print single-column"
	,"  -K    use termcap-names and BSD syntax"
	,"  -C    use termcap-names"
	,"  -F    compare terminfo-files"
	,"  -I    use terminfo-names"
	,"  -L    use long names"
	,"  -R subset (see manpage)"
	,"  -T    eliminate size limits (test)"
	,"  -U    eliminate post-processing of entries"
	,"  -D    print database locations"
	,"  -V    print version"
#if NCURSES_XNAMES
	,"  -a    with -F, list commented-out caps"
#endif
	,"  -c    list common capabilities"
	,"  -d    list different capabilities"
	,"  -e    format output for C initializer"
	,"  -E    format output as C tables"
	,"  -f    with -1, format complex strings"
	,"  -G    format %{number} to %'char'"
	,"  -g    format %'char' to %{number}"
	,"  -i    analyze initialization/reset"
	,"  -l    output terminfo names"
	,"  -n    list capabilities in neither"
	,"  -p    ignore padding specifiers"
	,"  -q    brief listing, removes headers"
	,"  -r    with -C, output in termcap form"
	,"  -r    with -F, resolve use-references"
	,"  -s [d|i|l|c] sort fields"
#if NCURSES_XNAMES
	,"  -t    suppress commented-out capabilities"
#endif
	,"  -u    produce source with 'use='"
	,"  -v number  (verbose)"
	,"  -w number  (width)"
#if NCURSES_XNAMES
	,"  -x    treat unknown capabilities as user-defined"
#endif
    };
    const size_t first = 3;
    const size_t last = SIZEOF(tbl);
    const size_t left = (last - first + 1) / 2 + first;
    size_t n;

    for (n = 0; n < left; n++) {
	size_t m = (n < first) ? last : n + left - first;
	if (m < last)
	    fprintf(stderr, "%-40.40s%s\n", tbl[n], tbl[m]);
	else
	    fprintf(stderr, "%s\n", tbl[n]);
    }
    ExitProgram(EXIT_FAILURE);
}