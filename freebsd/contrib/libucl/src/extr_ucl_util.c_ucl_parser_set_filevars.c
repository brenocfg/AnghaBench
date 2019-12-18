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
struct ucl_parser {int dummy; } ;
typedef  int /*<<< orphan*/  realbuf ;

/* Variables and functions */
 int PATH_MAX ; 
 char* dirname (char*) ; 
 char* getcwd (char*,int) ; 
 int /*<<< orphan*/  ucl_parser_register_variable (struct ucl_parser*,char*,char*) ; 
 int /*<<< orphan*/ * ucl_realpath (char const*,char*) ; 
 int /*<<< orphan*/  ucl_strlcpy (char*,char const*,int) ; 

bool
ucl_parser_set_filevars (struct ucl_parser *parser, const char *filename, bool need_expand)
{
	char realbuf[PATH_MAX], *curdir;

	if (filename != NULL) {
		if (need_expand) {
			if (ucl_realpath (filename, realbuf) == NULL) {
				return false;
			}
		}
		else {
			ucl_strlcpy (realbuf, filename, sizeof (realbuf));
		}

		/* Define variables */
		ucl_parser_register_variable (parser, "FILENAME", realbuf);
		curdir = dirname (realbuf);
		ucl_parser_register_variable (parser, "CURDIR", curdir);
	}
	else {
		/* Set everything from the current dir */
		curdir = getcwd (realbuf, sizeof (realbuf));
		ucl_parser_register_variable (parser, "FILENAME", "undef");
		ucl_parser_register_variable (parser, "CURDIR", curdir);
	}

	return true;
}