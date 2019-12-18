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
 unsigned int SIZEOF (char const**) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
usage(void)
{
    static const char *msg[] =
    {
	"Usage: tabs [options] [tabstop-list]"
	,""
	,"Options:"
	,"  -0       reset tabs"
	,"  -8       set tabs to standard interval"
	,"  -a       Assembler, IBM S/370, first format"
	,"  -a2      Assembler, IBM S/370, second format"
	,"  -c       COBOL, normal format"
	,"  -c2      COBOL compact format"
	,"  -c3      COBOL compact format extended"
	,"  -d       debug (show ruler with expected/actual tab positions)"
	,"  -f       FORTRAN"
	,"  -n       no-op (do not modify terminal settings)"
	,"  -p       PL/I"
	,"  -s       SNOBOL"
	,"  -u       UNIVAC 1100 Assembler"
	,"  -T name  use terminal type 'name'"
	,"  -V       print version"
	,""
	,"A tabstop-list is an ordered list of column numbers, e.g., 1,11,21"
	,"or 1,+10,+10 which is the same."
    };
    unsigned n;

    fflush(stdout);
    for (n = 0; n < SIZEOF(msg); ++n) {
	fprintf(stderr, "%s\n", msg[n]);
    }
    ExitProgram(EXIT_FAILURE);
}