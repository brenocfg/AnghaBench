#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct packref {int /*<<< orphan*/  flags; int /*<<< orphan*/  oid; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcache; int /*<<< orphan*/  gitpath; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_SYMREF ; 
 int /*<<< orphan*/  PACKREF_WAS_LOOSE ; 
 int /*<<< orphan*/  git__prefixcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_sortedcache_upsert (void**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_sortedcache_wlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (int /*<<< orphan*/ ) ; 
 int loose_parse_oid (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ loose_readbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int loose_lookup_to_packfile(refdb_fs_backend *backend, const char *name)
{
	int error = 0;
	git_buf ref_file = GIT_BUF_INIT;
	struct packref *ref = NULL;
	git_oid oid;

	/* if we fail to load the loose reference, assume someone changed
	 * the filesystem under us and skip it...
	 */
	if (loose_readbuffer(&ref_file, backend->gitpath, name) < 0) {
		git_error_clear();
		goto done;
	}

	/* skip symbolic refs */
	if (!git__prefixcmp(git_buf_cstr(&ref_file), GIT_SYMREF))
		goto done;

	/* parse OID from file */
	if ((error = loose_parse_oid(&oid, name, &ref_file)) < 0)
		goto done;

	git_sortedcache_wlock(backend->refcache);

	if (!(error = git_sortedcache_upsert(
			(void **)&ref, backend->refcache, name))) {

		git_oid_cpy(&ref->oid, &oid);
		ref->flags = PACKREF_WAS_LOOSE;
	}

	git_sortedcache_wunlock(backend->refcache);

done:
	git_buf_dispose(&ref_file);
	return error;
}