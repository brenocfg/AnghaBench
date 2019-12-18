#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* l_code; char* l_name; char** l_options; } ;

/* Variables and functions */
 char* DEFAULT_DEVICE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* lcd_drivertab ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void) 
{
    int		i, j;
    
    fprintf(stderr, "usage: %s [-v] [-d drivername] [-f device] [-o options] [args...]\n", progname);
    fprintf(stderr, "   -D      Increase debugging\n");
    fprintf(stderr, "   -f      Specify device, default is '%s'\n", DEFAULT_DEVICE);
    fprintf(stderr, "   -d      Specify driver, one of:\n");
    for (i = 0; lcd_drivertab[i].l_code != NULL; i++) {
	fprintf(stderr, "              %-10s (%s)%s\n", 
		lcd_drivertab[i].l_code, lcd_drivertab[i].l_name, (i == 0) ? " *default*" : "");
	if (lcd_drivertab[i].l_options[0] != NULL) {
	    
	    for (j = 0; lcd_drivertab[i].l_options[j] != NULL; j++)
		fprintf(stderr, "                  %s\n", lcd_drivertab[i].l_options[j]);
	}
    }
    fprintf(stderr, "  -o       Specify driver option string\n");
    fprintf(stderr, "  args     Message strings.  Embedded escapes supported:\n");
    fprintf(stderr, "                  \\b	Backspace\n");
    fprintf(stderr, "                  \\f	Clear display, home cursor\n");
    fprintf(stderr, "                  \\n	Newline\n");
    fprintf(stderr, "                  \\r	Carriage return\n");
    fprintf(stderr, "                  \\R	Reset display\n");
    fprintf(stderr, "                  \\v	Home cursor\n");
    fprintf(stderr, "                  \\\\	Literal \\\n");
    fprintf(stderr, "           If args not supplied, strings are read from standard input\n");
    exit(EX_USAGE);
}