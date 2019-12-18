#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdemitconf_t ;
struct TYPE_3__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int REG_NOMATCH ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 scalar_t__ match_funcname (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int regexec (int /*<<< orphan*/ *,char const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *find_funcname_matching_regexp(xdemitconf_t *xecfg, const char *start,
						 regex_t *regexp)
{
	int reg_error;
	regmatch_t match[1];
	while (1) {
		const char *bol, *eol;
		reg_error = regexec(regexp, start, 1, match, 0);
		if (reg_error == REG_NOMATCH)
			return NULL;
		else if (reg_error) {
			char errbuf[1024];
			regerror(reg_error, regexp, errbuf, 1024);
			die("-L parameter: regexec() failed: %s", errbuf);
		}
		/* determine extent of line matched */
		bol = start+match[0].rm_so;
		eol = start+match[0].rm_eo;
		while (bol > start && *bol != '\n')
			bol--;
		if (*bol == '\n')
			bol++;
		while (*eol && *eol != '\n')
			eol++;
		if (*eol == '\n')
			eol++;
		/* is it a funcname line? */
		if (match_funcname(xecfg, (char*) bol, (char*) eol))
			return bol;
		start = eol;
	}
}