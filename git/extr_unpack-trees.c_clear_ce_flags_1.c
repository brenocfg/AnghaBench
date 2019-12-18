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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct pattern_list {int dummy; } ;
struct index_state {int dummy; } ;
struct cache_entry {int ce_flags; char* name; } ;
typedef  enum pattern_match_result { ____Placeholder_pattern_match_result } pattern_match_result ;

/* Variables and functions */
 int MATCHED ; 
 int UNDECIDED ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 int ce_to_dtype (struct cache_entry*) ; 
 int clear_ce_flags_dir (struct index_state*,struct cache_entry**,int,struct strbuf*,scalar_t__,int,int,struct pattern_list*,int) ; 
 int path_matches_pattern_list (char*,int /*<<< orphan*/ ,char const*,int*,struct pattern_list*,struct index_state*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int clear_ce_flags_1(struct index_state *istate,
			    struct cache_entry **cache, int nr,
			    struct strbuf *prefix,
			    int select_mask, int clear_mask,
			    struct pattern_list *pl,
			    enum pattern_match_result default_match)
{
	struct cache_entry **cache_end = cache + nr;

	/*
	 * Process all entries that have the given prefix and meet
	 * select_mask condition
	 */
	while(cache != cache_end) {
		struct cache_entry *ce = *cache;
		const char *name, *slash;
		int len, dtype;
		enum pattern_match_result ret;

		if (select_mask && !(ce->ce_flags & select_mask)) {
			cache++;
			continue;
		}

		if (prefix->len && strncmp(ce->name, prefix->buf, prefix->len))
			break;

		name = ce->name + prefix->len;
		slash = strchr(name, '/');

		/* If it's a directory, try whole directory match first */
		if (slash) {
			int processed;

			len = slash - name;
			strbuf_add(prefix, name, len);

			processed = clear_ce_flags_dir(istate, cache, cache_end - cache,
						       prefix,
						       prefix->buf + prefix->len - len,
						       select_mask, clear_mask,
						       pl, default_match);

			/* clear_c_f_dir eats a whole dir already? */
			if (processed) {
				cache += processed;
				strbuf_setlen(prefix, prefix->len - len);
				continue;
			}

			strbuf_addch(prefix, '/');
			cache += clear_ce_flags_1(istate, cache, cache_end - cache,
						  prefix,
						  select_mask, clear_mask, pl,
						  default_match);
			strbuf_setlen(prefix, prefix->len - len - 1);
			continue;
		}

		/* Non-directory */
		dtype = ce_to_dtype(ce);
		ret = path_matches_pattern_list(ce->name,
						ce_namelen(ce),
						name, &dtype, pl, istate);
		if (ret == UNDECIDED)
			ret = default_match;
		if (ret == MATCHED)
			ce->ce_flags &= ~clear_mask;
		cache++;
	}
	return nr - (cache_end - cache);
}