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
typedef  char xdemitconf_t ;
struct userdiff_funcname {int /*<<< orphan*/  cflags; scalar_t__ pattern; } ;
struct userdiff_driver {struct userdiff_funcname funcname; } ;
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  char const* (* nth_line_fn_t ) (void*,long) ;

/* Variables and functions */
 int /*<<< orphan*/  REG_NEWLINE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  die (char*,char*,...) ; 
 char* find_funcname_matching_regexp (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ match_funcname (char*,char const*,char const*) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 struct userdiff_driver* userdiff_find_by_path (struct index_state*,char const*) ; 
 char* xcalloc (int,int) ; 
 int /*<<< orphan*/  xdiff_set_find_func (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static const char *parse_range_funcname(
	const char *arg, nth_line_fn_t nth_line_cb,
	void *cb_data, long lines, long anchor, long *begin, long *end,
	const char *path, struct index_state *istate)
{
	char *pattern;
	const char *term;
	struct userdiff_driver *drv;
	xdemitconf_t *xecfg = NULL;
	const char *start;
	const char *p;
	int reg_error;
	regex_t regexp;

	if (*arg == '^') {
		anchor = 1;
		arg++;
	}

	assert(*arg == ':');
	term = arg+1;
	while (*term && *term != ':') {
		if (*term == '\\' && *(term+1))
			term++;
		term++;
	}
	if (term == arg+1)
		return NULL;
	if (!begin) /* skip_range_arg case */
		return term;

	pattern = xstrndup(arg+1, term-(arg+1));

	anchor--; /* input is in human terms */
	start = nth_line_cb(cb_data, anchor);

	drv = userdiff_find_by_path(istate, path);
	if (drv && drv->funcname.pattern) {
		const struct userdiff_funcname *pe = &drv->funcname;
		xecfg = xcalloc(1, sizeof(*xecfg));
		xdiff_set_find_func(xecfg, pe->pattern, pe->cflags);
	}

	reg_error = regcomp(&regexp, pattern, REG_NEWLINE);
	if (reg_error) {
		char errbuf[1024];
		regerror(reg_error, &regexp, errbuf, 1024);
		die("-L parameter '%s': %s", pattern, errbuf);
	}

	p = find_funcname_matching_regexp(xecfg, (char*) start, &regexp);
	if (!p)
		die("-L parameter '%s' starting at line %ld: no match",
		    pattern, anchor + 1);
	*begin = 0;
	while (p > nth_line_cb(cb_data, *begin))
		(*begin)++;

	if (*begin >= lines)
		die("-L parameter '%s' matches at EOF", pattern);

	*end = *begin+1;
	while (*end < lines) {
		const char *bol = nth_line_cb(cb_data, *end);
		const char *eol = nth_line_cb(cb_data, *end+1);
		if (match_funcname(xecfg, bol, eol))
			break;
		(*end)++;
	}

	regfree(&regexp);
	free(xecfg);
	free(pattern);

	/* compensate for 1-based numbering */
	(*begin)++;

	return term;
}