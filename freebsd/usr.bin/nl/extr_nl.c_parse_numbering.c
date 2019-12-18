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
typedef  int /*<<< orphan*/  errorbuf ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  expr; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int NL_TEXTMAX ; 
 int REG_NEWLINE ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  number_all ; 
 int /*<<< orphan*/  number_none ; 
 int /*<<< orphan*/  number_nonempty ; 
 int /*<<< orphan*/  number_regex ; 
 TYPE_1__* numbering_properties ; 
 int regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
parse_numbering(const char *argstr, int section)
{
	int error;
	char errorbuf[NL_TEXTMAX];

	switch (argstr[0]) {
	case 'a':
		numbering_properties[section].type = number_all;
		break;
	case 'n':
		numbering_properties[section].type = number_none;
		break;
	case 't':
		numbering_properties[section].type = number_nonempty;
		break;
	case 'p':
		/* If there was a previous expression, throw it away. */
		if (numbering_properties[section].type == number_regex)
			regfree(&numbering_properties[section].expr);
		else
			numbering_properties[section].type = number_regex;

		/* Compile/validate the supplied regular expression. */
		if ((error = regcomp(&numbering_properties[section].expr,
		    &argstr[1], REG_NEWLINE|REG_NOSUB)) != 0) {
			(void)regerror(error,
			    &numbering_properties[section].expr,
			    errorbuf, sizeof (errorbuf));
			errx(EXIT_FAILURE,
			    "%s expr: %s -- %s",
			    numbering_properties[section].name, errorbuf,
			    &argstr[1]);
		}
		break;
	default:
		errx(EXIT_FAILURE,
		    "illegal %s line numbering type -- %s",
		    numbering_properties[section].name, argstr);
	}
}