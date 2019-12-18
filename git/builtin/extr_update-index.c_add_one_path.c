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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct cache_entry {int ce_namelen; int /*<<< orphan*/  oid; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int /*<<< orphan*/  HASH_WRITE_OBJECT ; 
 scalar_t__ add_cache_entry (struct cache_entry*,int) ; 
 scalar_t__ allow_add ; 
 scalar_t__ allow_replace ; 
 int /*<<< orphan*/  ce_match_stat (struct cache_entry const*,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_mode_from_stat (struct cache_entry const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  create_ce_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  fill_stat_cache_info (int /*<<< orphan*/ *,struct cache_entry*,struct stat*) ; 
 scalar_t__ index_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,struct stat*,int /*<<< orphan*/ ) ; 
 scalar_t__ info_only ; 
 struct cache_entry* make_empty_cache_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static int add_one_path(const struct cache_entry *old, const char *path, int len, struct stat *st)
{
	int option;
	struct cache_entry *ce;

	/* Was the old index entry already up-to-date? */
	if (old && !ce_stage(old) && !ce_match_stat(old, st, 0))
		return 0;

	ce = make_empty_cache_entry(&the_index, len);
	memcpy(ce->name, path, len);
	ce->ce_flags = create_ce_flags(0);
	ce->ce_namelen = len;
	fill_stat_cache_info(&the_index, ce, st);
	ce->ce_mode = ce_mode_from_stat(old, st->st_mode);

	if (index_path(&the_index, &ce->oid, path, st,
		       info_only ? 0 : HASH_WRITE_OBJECT)) {
		discard_cache_entry(ce);
		return -1;
	}
	option = allow_add ? ADD_CACHE_OK_TO_ADD : 0;
	option |= allow_replace ? ADD_CACHE_OK_TO_REPLACE : 0;
	if (add_cache_entry(ce, option)) {
		discard_cache_entry(ce);
		return error("%s: cannot add to the index - missing --add option?", path);
	}
	return 0;
}