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
struct pathspec {scalar_t__ nr; } ;
struct module_list {scalar_t__ nr; struct cache_entry const** entries; int /*<<< orphan*/  alloc; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cache_entry const**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATHSPEC_PREFER_FULL ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  match_pathspec (int /*<<< orphan*/ *,struct pathspec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  parse_pathspec (struct pathspec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const**) ; 
 scalar_t__ read_cache () ; 
 scalar_t__ report_path_error (char*,struct pathspec*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_index ; 
 char* xcalloc (scalar_t__,int) ; 

__attribute__((used)) static int module_list_compute(int argc, const char **argv,
			       const char *prefix,
			       struct pathspec *pathspec,
			       struct module_list *list)
{
	int i, result = 0;
	char *ps_matched = NULL;
	parse_pathspec(pathspec, 0,
		       PATHSPEC_PREFER_FULL,
		       prefix, argv);

	if (pathspec->nr)
		ps_matched = xcalloc(pathspec->nr, 1);

	if (read_cache() < 0)
		die(_("index file corrupt"));

	for (i = 0; i < active_nr; i++) {
		const struct cache_entry *ce = active_cache[i];

		if (!match_pathspec(&the_index, pathspec, ce->name, ce_namelen(ce),
				    0, ps_matched, 1) ||
		    !S_ISGITLINK(ce->ce_mode))
			continue;

		ALLOC_GROW(list->entries, list->nr + 1, list->alloc);
		list->entries[list->nr++] = ce;
		while (i + 1 < active_nr &&
		       !strcmp(ce->name, active_cache[i + 1]->name))
			/*
			 * Skip entries with the same name in different stages
			 * to make sure an entry is returned only once.
			 */
			i++;
	}

	if (ps_matched && report_path_error(ps_matched, pathspec))
		result = -1;

	free(ps_matched);

	return result;
}