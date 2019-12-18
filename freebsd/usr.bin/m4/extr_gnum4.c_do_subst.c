#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int rm_eo; int rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
struct TYPE_11__ {scalar_t__ re_nsub; } ;
typedef  TYPE_2__ regex_t ;

/* Variables and functions */
 int REG_NOMATCH ; 
 int REG_NOTBOL ; 
 int /*<<< orphan*/  add_replace (char const*,TYPE_2__*,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  addchar (char const) ; 
 int /*<<< orphan*/  addchars (char const*,int) ; 
 int /*<<< orphan*/  exit_regerror (int,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  pbstr (char const*) ; 
 int regexec (TYPE_2__*,char const*,scalar_t__,TYPE_1__*,int) ; 

__attribute__((used)) static void
do_subst(const char *string, regex_t *re, const char *source,
    const char *replace, regmatch_t *pm)
{
	int error;
	int flags = 0;
	const char *last_match = NULL;

	while ((error = regexec(re, string, re->re_nsub+1, pm, flags)) == 0) {
		if (pm[0].rm_eo != 0) {
			if (string[pm[0].rm_eo-1] == '\n')
				flags = 0;
			else
				flags = REG_NOTBOL;
		}

		/* NULL length matches are special... We use the `vi-mode'
		 * rule: don't allow a NULL-match at the last match
		 * position.
		 */
		if (pm[0].rm_so == pm[0].rm_eo &&
		    string + pm[0].rm_so == last_match) {
			if (*string == '\0')
				return;
			addchar(*string);
			if (*string++ == '\n')
				flags = 0;
			else
				flags = REG_NOTBOL;
			continue;
		}
		last_match = string + pm[0].rm_so;
		addchars(string, pm[0].rm_so);
		add_replace(string, re, replace, pm);
		string += pm[0].rm_eo;
	}
	if (error != REG_NOMATCH)
		exit_regerror(error, re, source);
	pbstr(string);
}