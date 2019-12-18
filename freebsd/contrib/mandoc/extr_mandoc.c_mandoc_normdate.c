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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ macroset; } ;
struct roff_man {TYPE_1__ meta; scalar_t__ quick; } ;

/* Variables and functions */
 scalar_t__ MACROSET_MDOC ; 
 int /*<<< orphan*/  MANDOCERR_DATE_BAD ; 
 int /*<<< orphan*/  MANDOCERR_DATE_FUTURE ; 
 int /*<<< orphan*/  MANDOCERR_DATE_LEGACY ; 
 int /*<<< orphan*/  MANDOCERR_DATE_MISSING ; 
 int /*<<< orphan*/  MANDOCERR_DATE_NORM ; 
 scalar_t__ a2time (scalar_t__*,char*,char*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,...) ; 
 char* mandoc_strdup (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 char* time2a (scalar_t__) ; 

char *
mandoc_normdate(struct roff_man *man, char *in, int ln, int pos)
{
	char		*cp;
	time_t		 t;

	if (man->quick)
		return mandoc_strdup(in == NULL ? "" : in);

	/* No date specified: use today's date. */

	if (in == NULL || *in == '\0')
		mandoc_msg(MANDOCERR_DATE_MISSING, ln, pos, NULL);
	if (in == NULL || *in == '\0' || strcmp(in, "$" "Mdocdate$") == 0)
		return time2a(time(NULL));

	/* Valid mdoc(7) date format. */

	if (a2time(&t, "$" "Mdocdate: %b %d %Y $", in) ||
	    a2time(&t, "%b %d, %Y", in)) {
		cp = time2a(t);
		if (t > time(NULL) + 86400)
			mandoc_msg(MANDOCERR_DATE_FUTURE, ln, pos, "%s", cp);
		else if (*in != '$' && strcmp(in, cp) != 0)
			mandoc_msg(MANDOCERR_DATE_NORM, ln, pos, "%s", cp);
		return cp;
	}

	/* In man(7), do not warn about the legacy format. */

	if (a2time(&t, "%Y-%m-%d", in) == 0)
		mandoc_msg(MANDOCERR_DATE_BAD, ln, pos, "%s", in);
	else if (t > time(NULL) + 86400)
		mandoc_msg(MANDOCERR_DATE_FUTURE, ln, pos, "%s", in);
	else if (man->meta.macroset == MACROSET_MDOC)
		mandoc_msg(MANDOCERR_DATE_LEGACY, ln, pos, "Dd %s", in);

	/* Use any non-mdoc(7) date verbatim. */

	return mandoc_strdup(in);
}