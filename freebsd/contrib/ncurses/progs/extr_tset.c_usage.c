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
typedef  int /*<<< orphan*/  tbl ;

/* Variables and functions */
 char* _nc_progname ; 
 int /*<<< orphan*/  exit_error () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
    static const char *tbl[] =
    {
	""
	,"Options:"
	,"  -c          set control characters"
	,"  -e ch       erase character"
	,"  -I          no initialization strings"
	,"  -i ch       interrupt character"
	,"  -k ch       kill character"
	,"  -m mapping  map identifier to type"
	,"  -Q          do not output control key settings"
	,"  -r          display term on stderr"
	,"  -s          output TERM set command"
	,"  -V          print curses-version"
	,"  -w          set window-size"
    };
    unsigned n;
    (void) fprintf(stderr, "Usage: %s [options] [terminal]\n", _nc_progname);
    for (n = 0; n < sizeof(tbl) / sizeof(tbl[0]); ++n)
	fprintf(stderr, "%s\n", tbl[n]);
    exit_error();
    /* NOTREACHED */
}