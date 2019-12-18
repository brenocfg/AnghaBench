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
struct date_mode {int local; int /*<<< orphan*/  strftime_fmt; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_STRFTIME ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ isatty (int) ; 
 scalar_t__ pager_in_use () ; 
 int /*<<< orphan*/  parse_date_type (char const*,char const**) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void parse_date_format(const char *format, struct date_mode *mode)
{
	const char *p;

	/* "auto:foo" is "if tty/pager, then foo, otherwise normal" */
	if (skip_prefix(format, "auto:", &p)) {
		if (isatty(1) || pager_in_use())
			format = p;
		else
			format = "default";
	}

	/* historical alias */
	if (!strcmp(format, "local"))
		format = "default-local";

	mode->type = parse_date_type(format, &p);
	mode->local = 0;

	if (skip_prefix(p, "-local", &p))
		mode->local = 1;

	if (mode->type == DATE_STRFTIME) {
		if (!skip_prefix(p, ":", &p))
			die("date format missing colon separator: %s", format);
		mode->strftime_fmt = xstrdup(p);
	} else if (*p)
		die("unknown date format %s", format);
}