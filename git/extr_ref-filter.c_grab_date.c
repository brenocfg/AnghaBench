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
typedef  scalar_t__ timestamp_t ;
struct date_mode {int /*<<< orphan*/  member_0; } ;
struct atom_value {scalar_t__ value; void* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_NORMAL ; 
 scalar_t__ ERANGE ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 scalar_t__ TIME_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  parse_date_format (char const*,struct date_mode*) ; 
 scalar_t__ parse_timestamp (char const*,char**,int) ; 
 char* show_date (scalar_t__,long,struct date_mode*) ; 
 char* strchr (char const*,char) ; 
 char* strstr (char const*,char*) ; 
 long strtol (char*,int /*<<< orphan*/ *,int) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static void grab_date(const char *buf, struct atom_value *v, const char *atomname)
{
	const char *eoemail = strstr(buf, "> ");
	char *zone;
	timestamp_t timestamp;
	long tz;
	struct date_mode date_mode = { DATE_NORMAL };
	const char *formatp;

	/*
	 * We got here because atomname ends in "date" or "date<something>";
	 * it's not possible that <something> is not ":<format>" because
	 * parse_ref_filter_atom() wouldn't have allowed it, so we can assume that no
	 * ":" means no format is specified, and use the default.
	 */
	formatp = strchr(atomname, ':');
	if (formatp != NULL) {
		formatp++;
		parse_date_format(formatp, &date_mode);
	}

	if (!eoemail)
		goto bad;
	timestamp = parse_timestamp(eoemail + 2, &zone, 10);
	if (timestamp == TIME_MAX)
		goto bad;
	tz = strtol(zone, NULL, 10);
	if ((tz == LONG_MIN || tz == LONG_MAX) && errno == ERANGE)
		goto bad;
	v->s = xstrdup(show_date(timestamp, tz, &date_mode));
	v->value = timestamp;
	return;
 bad:
	v->s = xstrdup("");
	v->value = 0;
}