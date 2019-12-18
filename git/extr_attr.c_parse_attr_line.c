#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; int len; } ;
struct TYPE_3__ {char* pattern; int flags; int /*<<< orphan*/  nowildcardlen; int /*<<< orphan*/  patternlen; } ;
struct TYPE_4__ {TYPE_1__ pat; int /*<<< orphan*/  attr; } ;
struct match_attr {int is_macro; int num_attr; int /*<<< orphan*/ * state; TYPE_2__ u; } ;
struct attr_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRIBUTE_MACRO_PREFIX ; 
 int PATTERN_FLAG_NEGATIVE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  attr_name_valid (char const*,int) ; 
 int /*<<< orphan*/  blank ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int) ; 
 int /*<<< orphan*/  free (struct match_attr*) ; 
 int /*<<< orphan*/  git_attr_internal (char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* parse_attr (char const*,int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_path_pattern (char**,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_invalid_attr (char const*,int,char const*,int) ; 
 scalar_t__ starts_with (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int strcspn (char const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int strspn (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unquote_c_style (struct strbuf*,char const*,char const**) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 
 struct match_attr* xcalloc (int,int) ; 

__attribute__((used)) static struct match_attr *parse_attr_line(const char *line, const char *src,
					  int lineno, int macro_ok)
{
	int namelen;
	int num_attr, i;
	const char *cp, *name, *states;
	struct match_attr *res = NULL;
	int is_macro;
	struct strbuf pattern = STRBUF_INIT;

	cp = line + strspn(line, blank);
	if (!*cp || *cp == '#')
		return NULL;
	name = cp;

	if (*cp == '"' && !unquote_c_style(&pattern, name, &states)) {
		name = pattern.buf;
		namelen = pattern.len;
	} else {
		namelen = strcspn(name, blank);
		states = name + namelen;
	}

	if (strlen(ATTRIBUTE_MACRO_PREFIX) < namelen &&
	    starts_with(name, ATTRIBUTE_MACRO_PREFIX)) {
		if (!macro_ok) {
			fprintf_ln(stderr, _("%s not allowed: %s:%d"),
				   name, src, lineno);
			goto fail_return;
		}
		is_macro = 1;
		name += strlen(ATTRIBUTE_MACRO_PREFIX);
		name += strspn(name, blank);
		namelen = strcspn(name, blank);
		if (!attr_name_valid(name, namelen)) {
			report_invalid_attr(name, namelen, src, lineno);
			goto fail_return;
		}
	}
	else
		is_macro = 0;

	states += strspn(states, blank);

	/* First pass to count the attr_states */
	for (cp = states, num_attr = 0; *cp; num_attr++) {
		cp = parse_attr(src, lineno, cp, NULL);
		if (!cp)
			goto fail_return;
	}

	res = xcalloc(1,
		      sizeof(*res) +
		      sizeof(struct attr_state) * num_attr +
		      (is_macro ? 0 : namelen + 1));
	if (is_macro) {
		res->u.attr = git_attr_internal(name, namelen);
	} else {
		char *p = (char *)&(res->state[num_attr]);
		memcpy(p, name, namelen);
		res->u.pat.pattern = p;
		parse_path_pattern(&res->u.pat.pattern,
				      &res->u.pat.patternlen,
				      &res->u.pat.flags,
				      &res->u.pat.nowildcardlen);
		if (res->u.pat.flags & PATTERN_FLAG_NEGATIVE) {
			warning(_("Negative patterns are ignored in git attributes\n"
				  "Use '\\!' for literal leading exclamation."));
			goto fail_return;
		}
	}
	res->is_macro = is_macro;
	res->num_attr = num_attr;

	/* Second pass to fill the attr_states */
	for (cp = states, i = 0; *cp; i++) {
		cp = parse_attr(src, lineno, cp, &(res->state[i]));
	}

	strbuf_release(&pattern);
	return res;

fail_return:
	strbuf_release(&pattern);
	free(res);
	return NULL;
}