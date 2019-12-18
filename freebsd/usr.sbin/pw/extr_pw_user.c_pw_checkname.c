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
typedef  int /*<<< orphan*/  showch ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int LOGNAMESIZE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const) ; 
 int /*<<< orphan*/ * strchr (char const*,char const) ; 

char *
pw_checkname(char *name, int gecos)
{
	char showch[8];
	const char *badchars, *ch, *showtype;
	int reject;

	ch = name;
	reject = 0;
	if (gecos) {
		/* See if the name is valid as a gecos (comment) field. */
		badchars = ":";
		showtype = "gecos field";
	} else {
		/* See if the name is valid as a userid or group. */
		badchars = " ,\t:+&#%$^()!@~*?<>=|\\/\"";
		showtype = "userid/group name";
		/* Userids and groups can not have a leading '-'. */
		if (*ch == '-')
			reject = 1;
	}
	if (!reject) {
		while (*ch) {
			if (strchr(badchars, *ch) != NULL ||
			    (!gecos && *ch < ' ') ||
			    *ch == 127) {
				reject = 1;
				break;
			}
			/* 8-bit characters are only allowed in GECOS fields */
			if (!gecos && (*ch & 0x80)) {
				reject = 1;
				break;
			}
			ch++;
		}
	}
	/*
	 * A `$' is allowed as the final character for userids and groups,
	 * mainly for the benefit of samba.
	 */
	if (reject && !gecos) {
		if (*ch == '$' && *(ch + 1) == '\0') {
			reject = 0;
			ch++;
		}
	}
	if (reject) {
		snprintf(showch, sizeof(showch), (*ch >= ' ' && *ch < 127)
		    ? "`%c'" : "0x%02x", *ch);
		errx(EX_DATAERR, "invalid character %s at position %td in %s",
		    showch, (ch - name), showtype);
	}
	if (!gecos && (ch - name) > LOGNAMESIZE)
		errx(EX_USAGE, "name too long `%s' (max is %d)", name,
		    LOGNAMESIZE);

	return (name);
}