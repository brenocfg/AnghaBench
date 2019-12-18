#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct cache_entry {int ce_namelen; int /*<<< orphan*/  oid; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; } ;
struct apply_state {TYPE_1__* repo; int /*<<< orphan*/  cached; scalar_t__ ita_only; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CACHE_OK_TO_ADD ; 
 int /*<<< orphan*/  CE_INTENT_TO_ADD ; 
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_index_entry (int /*<<< orphan*/ ,struct cache_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blob_type ; 
 int /*<<< orphan*/  create_ce_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ce_mode (unsigned int) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fill_stat_cache_info (int /*<<< orphan*/ ,struct cache_entry*,struct stat*) ; 
 scalar_t__ get_oid_hex (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 struct cache_entry* make_empty_cache_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  set_object_name_for_intent_to_add_entry (struct cache_entry*) ; 
 int /*<<< orphan*/  skip_prefix (void*,char*,char const**) ; 
 int strlen (char const*) ; 
 scalar_t__ write_object_file (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_index_file(struct apply_state *state,
			  const char *path,
			  unsigned mode,
			  void *buf,
			  unsigned long size)
{
	struct stat st;
	struct cache_entry *ce;
	int namelen = strlen(path);

	ce = make_empty_cache_entry(state->repo->index, namelen);
	memcpy(ce->name, path, namelen);
	ce->ce_mode = create_ce_mode(mode);
	ce->ce_flags = create_ce_flags(0);
	ce->ce_namelen = namelen;
	if (state->ita_only) {
		ce->ce_flags |= CE_INTENT_TO_ADD;
		set_object_name_for_intent_to_add_entry(ce);
	} else if (S_ISGITLINK(mode)) {
		const char *s;

		if (!skip_prefix(buf, "Subproject commit ", &s) ||
		    get_oid_hex(s, &ce->oid)) {
			discard_cache_entry(ce);
			return error(_("corrupt patch for submodule %s"), path);
		}
	} else {
		if (!state->cached) {
			if (lstat(path, &st) < 0) {
				discard_cache_entry(ce);
				return error_errno(_("unable to stat newly "
						     "created file '%s'"),
						   path);
			}
			fill_stat_cache_info(state->repo->index, ce, &st);
		}
		if (write_object_file(buf, size, blob_type, &ce->oid) < 0) {
			discard_cache_entry(ce);
			return error(_("unable to create backing store "
				       "for newly created file %s"), path);
		}
	}
	if (add_index_entry(state->repo->index, ce, ADD_CACHE_OK_TO_ADD) < 0) {
		discard_cache_entry(ce);
		return error(_("unable to add cache entry for %s"), path);
	}

	return 0;
}