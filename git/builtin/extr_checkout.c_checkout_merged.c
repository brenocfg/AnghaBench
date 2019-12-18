#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  threeway ;
struct object_id {int dummy; } ;
struct checkout {int /*<<< orphan*/  istate; } ;
struct cache_entry {char* name; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ mmfile_t ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ mmbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int /*<<< orphan*/  blob_type ; 
 int ce_stage (struct cache_entry*) ; 
 int checkout_entry (struct cache_entry*,struct checkout const*,int /*<<< orphan*/ *,int*) ; 
 unsigned int create_ce_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 int ll_merge (TYPE_2__*,char const*,TYPE_1__*,char*,TYPE_1__*,char*,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cache_entry* make_transient_cache_entry (unsigned int,struct object_id*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct object_id*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_mmblob (TYPE_1__*,struct object_id*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

__attribute__((used)) static int checkout_merged(int pos, const struct checkout *state, int *nr_checkouts)
{
	struct cache_entry *ce = active_cache[pos];
	const char *path = ce->name;
	mmfile_t ancestor, ours, theirs;
	int status;
	struct object_id oid;
	mmbuffer_t result_buf;
	struct object_id threeway[3];
	unsigned mode = 0;

	memset(threeway, 0, sizeof(threeway));
	while (pos < active_nr) {
		int stage;
		stage = ce_stage(ce);
		if (!stage || strcmp(path, ce->name))
			break;
		oidcpy(&threeway[stage - 1], &ce->oid);
		if (stage == 2)
			mode = create_ce_mode(ce->ce_mode);
		pos++;
		ce = active_cache[pos];
	}
	if (is_null_oid(&threeway[1]) || is_null_oid(&threeway[2]))
		return error(_("path '%s' does not have necessary versions"), path);

	read_mmblob(&ancestor, &threeway[0]);
	read_mmblob(&ours, &threeway[1]);
	read_mmblob(&theirs, &threeway[2]);

	/*
	 * NEEDSWORK: re-create conflicts from merges with
	 * merge.renormalize set, too
	 */
	status = ll_merge(&result_buf, path, &ancestor, "base",
			  &ours, "ours", &theirs, "theirs",
			  state->istate, NULL);
	free(ancestor.ptr);
	free(ours.ptr);
	free(theirs.ptr);
	if (status < 0 || !result_buf.ptr) {
		free(result_buf.ptr);
		return error(_("path '%s': cannot merge"), path);
	}

	/*
	 * NEEDSWORK:
	 * There is absolutely no reason to write this as a blob object
	 * and create a phony cache entry.  This hack is primarily to get
	 * to the write_entry() machinery that massages the contents to
	 * work-tree format and writes out which only allows it for a
	 * cache entry.  The code in write_entry() needs to be refactored
	 * to allow us to feed a <buffer, size, mode> instead of a cache
	 * entry.  Such a refactoring would help merge_recursive as well
	 * (it also writes the merge result to the object database even
	 * when it may contain conflicts).
	 */
	if (write_object_file(result_buf.ptr, result_buf.size, blob_type, &oid))
		die(_("Unable to add merge result for '%s'"), path);
	free(result_buf.ptr);
	ce = make_transient_cache_entry(mode, &oid, path, 2);
	if (!ce)
		die(_("make_cache_entry failed for path '%s'"), path);
	status = checkout_entry(ce, state, NULL, nr_checkouts);
	discard_cache_entry(ce);
	return status;
}