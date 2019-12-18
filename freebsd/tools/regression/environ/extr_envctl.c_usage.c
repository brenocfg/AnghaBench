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
 char* basename (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(const char *program)
{
	fprintf(stderr, "Usage:  %s [-DGUchrt] [-c 1|2|3|4] [-bgu name] "
	    "[-p name=value]\n"
	    "\t[(-S|-s name) value overwrite]\n\n"
	    "Options:\n"
	    "  -D\t\t\t\tDump environ\n"
	    "  -G name\t\t\tgetenv(NULL)\n"
	    "  -S value overwrite\t\tsetenv(NULL, value, overwrite)\n"
	    "  -U\t\t\t\tunsetenv(NULL)\n"
	    "  -b name\t\t\tblank the 'name=$name' entry, corrupting it\n"
	    "  -c 1|2|3|4\t\t\tClear environ variable using method:\n"
	    "\t\t\t\t1 - set environ to NULL pointer\n"
	    "\t\t\t\t2 - set environ[0] to NULL pointer\n"
	    "\t\t\t\t3 - set environ to calloc()'d NULL-terminated array\n"
	    "\t\t\t\t4 - set environ to static NULL-terminated array\n"
	    "  -g name\t\t\tgetenv(name)\n"
	    "  -h\t\t\t\tHelp\n"
	    "  -p name=value\t\t\tputenv(name=value)\n"
	    "  -r\t\t\t\treplace environ with { \"FOO=bar\", NULL }\n"
	    "  -s name value overwrite\tsetenv(name, value, overwrite)\n"
	    "  -t\t\t\t\tOutput is suitable for testing (no newlines)\n"
	    "  -u name\t\t\tunsetenv(name)\n",
	    basename(program));

	return;
}