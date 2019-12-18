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
struct index_state {int dummy; } ;
struct cache_entry {int ce_namelen; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  create_ce_flags (int) ; 
 int /*<<< orphan*/  create_ce_mode (unsigned int) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 struct cache_entry* make_empty_cache_entry (struct index_state*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 struct cache_entry* refresh_cache_entry (struct index_state*,struct cache_entry*,unsigned int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  verify_path (char const*,unsigned int) ; 

struct cache_entry *make_cache_entry(struct index_state *istate,
				     unsigned int mode,
				     const struct object_id *oid,
				     const char *path,
				     int stage,
				     unsigned int refresh_options)
{
	struct cache_entry *ce, *ret;
	int len;

	if (!verify_path(path, mode)) {
		error(_("invalid path '%s'"), path);
		return NULL;
	}

	len = strlen(path);
	ce = make_empty_cache_entry(istate, len);

	oidcpy(&ce->oid, oid);
	memcpy(ce->name, path, len);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = len;
	ce->ce_mode = create_ce_mode(mode);

	ret = refresh_cache_entry(istate, ce, refresh_options);
	if (ret != ce)
		discard_cache_entry(ce);
	return ret;
}