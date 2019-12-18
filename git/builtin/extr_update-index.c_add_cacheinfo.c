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
struct object_id {int dummy; } ;
struct cache_entry {int ce_namelen; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int /*<<< orphan*/  CE_VALID ; 
 scalar_t__ add_cache_entry (struct cache_entry*,int) ; 
 scalar_t__ allow_add ; 
 scalar_t__ allow_replace ; 
 scalar_t__ assume_unchanged ; 
 int /*<<< orphan*/  create_ce_flags (int) ; 
 int /*<<< orphan*/  create_ce_mode (unsigned int) ; 
 int error (char*,char const*) ; 
 struct cache_entry* make_empty_cache_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  report (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  verify_path (char const*,unsigned int) ; 

__attribute__((used)) static int add_cacheinfo(unsigned int mode, const struct object_id *oid,
			 const char *path, int stage)
{
	int len, option;
	struct cache_entry *ce;

	if (!verify_path(path, mode))
		return error("Invalid path '%s'", path);

	len = strlen(path);
	ce = make_empty_cache_entry(&the_index, len);

	oidcpy(&ce->oid, oid);
	memcpy(ce->name, path, len);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = len;
	ce->ce_mode = create_ce_mode(mode);
	if (assume_unchanged)
		ce->ce_flags |= CE_VALID;
	option = allow_add ? ADD_CACHE_OK_TO_ADD : 0;
	option |= allow_replace ? ADD_CACHE_OK_TO_REPLACE : 0;
	if (add_cache_entry(ce, option))
		return error("%s: cannot add to the index - missing --add option?",
			     path);
	report("add '%s'", path);
	return 0;
}