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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct ref_store {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** ref_rev_parse_rules ; 
 scalar_t__ refs_ref_exists (struct ref_store*,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,char*) ; 
 int /*<<< orphan*/  st_add (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  st_mult (int,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char const*,int,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int strlen (char*) ; 
 char** xmalloc (int /*<<< orphan*/ ) ; 
 scalar_t__ xsnprintf (char*,size_t,char*,int,char*) ; 
 char* xstrdup (char const*) ; 

char *refs_shorten_unambiguous_ref(struct ref_store *refs,
				   const char *refname, int strict)
{
	int i;
	static char **scanf_fmts;
	static int nr_rules;
	char *short_name;
	struct strbuf resolved_buf = STRBUF_INIT;

	if (!nr_rules) {
		/*
		 * Pre-generate scanf formats from ref_rev_parse_rules[].
		 * Generate a format suitable for scanf from a
		 * ref_rev_parse_rules rule by interpolating "%s" at the
		 * location of the "%.*s".
		 */
		size_t total_len = 0;
		size_t offset = 0;

		/* the rule list is NULL terminated, count them first */
		for (nr_rules = 0; ref_rev_parse_rules[nr_rules]; nr_rules++)
			/* -2 for strlen("%.*s") - strlen("%s"); +1 for NUL */
			total_len += strlen(ref_rev_parse_rules[nr_rules]) - 2 + 1;

		scanf_fmts = xmalloc(st_add(st_mult(sizeof(char *), nr_rules), total_len));

		offset = 0;
		for (i = 0; i < nr_rules; i++) {
			assert(offset < total_len);
			scanf_fmts[i] = (char *)&scanf_fmts[nr_rules] + offset;
			offset += xsnprintf(scanf_fmts[i], total_len - offset,
					    ref_rev_parse_rules[i], 2, "%s") + 1;
		}
	}

	/* bail out if there are no rules */
	if (!nr_rules)
		return xstrdup(refname);

	/* buffer for scanf result, at most refname must fit */
	short_name = xstrdup(refname);

	/* skip first rule, it will always match */
	for (i = nr_rules - 1; i > 0 ; --i) {
		int j;
		int rules_to_fail = i;
		int short_name_len;

		if (1 != sscanf(refname, scanf_fmts[i], short_name))
			continue;

		short_name_len = strlen(short_name);

		/*
		 * in strict mode, all (except the matched one) rules
		 * must fail to resolve to a valid non-ambiguous ref
		 */
		if (strict)
			rules_to_fail = nr_rules;

		/*
		 * check if the short name resolves to a valid ref,
		 * but use only rules prior to the matched one
		 */
		for (j = 0; j < rules_to_fail; j++) {
			const char *rule = ref_rev_parse_rules[j];

			/* skip matched rule */
			if (i == j)
				continue;

			/*
			 * the short name is ambiguous, if it resolves
			 * (with this previous rule) to a valid ref
			 * read_ref() returns 0 on success
			 */
			strbuf_reset(&resolved_buf);
			strbuf_addf(&resolved_buf, rule,
				    short_name_len, short_name);
			if (refs_ref_exists(refs, resolved_buf.buf))
				break;
		}

		/*
		 * short name is non-ambiguous if all previous rules
		 * haven't resolved to a valid ref
		 */
		if (j == rules_to_fail) {
			strbuf_release(&resolved_buf);
			return short_name;
		}
	}

	strbuf_release(&resolved_buf);
	free(short_name);
	return xstrdup(refname);
}