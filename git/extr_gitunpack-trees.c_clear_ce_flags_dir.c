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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct index_state {int dummy; } ;
struct exclude_list {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DT_DIR ; 
 int clear_ce_flags_1 (struct index_state*,struct cache_entry**,int,struct strbuf*,int,int,struct exclude_list*,int) ; 
 int is_excluded_from_list (int /*<<< orphan*/ ,scalar_t__,char*,int*,struct exclude_list*,struct index_state*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int clear_ce_flags_dir(struct index_state *istate,
			      struct cache_entry **cache, int nr,
			      struct strbuf *prefix,
			      char *basename,
			      int select_mask, int clear_mask,
			      struct exclude_list *el, int defval)
{
	struct cache_entry **cache_end;
	int dtype = DT_DIR;
	int ret = is_excluded_from_list(prefix->buf, prefix->len,
					basename, &dtype, el, istate);
	int rc;

	strbuf_addch(prefix, '/');

	/* If undecided, use matching result of parent dir in defval */
	if (ret < 0)
		ret = defval;

	for (cache_end = cache; cache_end != cache + nr; cache_end++) {
		struct cache_entry *ce = *cache_end;
		if (strncmp(ce->name, prefix->buf, prefix->len))
			break;
	}

	/*
	 * TODO: check el, if there are no patterns that may conflict
	 * with ret (iow, we know in advance the incl/excl
	 * decision for the entire directory), clear flag here without
	 * calling clear_ce_flags_1(). That function will call
	 * the expensive is_excluded_from_list() on every entry.
	 */
	rc = clear_ce_flags_1(istate, cache, cache_end - cache,
			      prefix,
			      select_mask, clear_mask,
			      el, ret);
	strbuf_setlen(prefix, prefix->len - 1);
	return rc;
}