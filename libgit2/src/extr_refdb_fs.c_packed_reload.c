#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct packref {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  peel; int /*<<< orphan*/  oid; } ;
struct TYPE_7__ {scalar_t__ peeling_mode; int /*<<< orphan*/  refcache; int /*<<< orphan*/  gitpath; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_8__ {int size; scalar_t__ ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 scalar_t__ GIT_OID_HEXSZ ; 
 char const* GIT_REFS_TAGS_DIR ; 
 int /*<<< orphan*/  PACKREF_CANNOT_PEEL ; 
 int /*<<< orphan*/  PACKREF_HAS_PEEL ; 
 scalar_t__ PEELING_FULL ; 
 scalar_t__ PEELING_NONE ; 
 scalar_t__ PEELING_STANDARD ; 
 scalar_t__ git__prefixcmp (char*,char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_sortedcache_clear (int /*<<< orphan*/ ,int) ; 
 int git_sortedcache_lockandload (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ git_sortedcache_upsert (void**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

__attribute__((used)) static int packed_reload(refdb_fs_backend *backend)
{
	int error;
	git_buf packedrefs = GIT_BUF_INIT;
	char *scan, *eof, *eol;

	if (!backend->gitpath)
		return 0;

	error = git_sortedcache_lockandload(backend->refcache, &packedrefs);

	/*
	 * If we can't find the packed-refs, clear table and return.
	 * Any other error just gets passed through.
	 * If no error, and file wasn't changed, just return.
	 * Anything else means we need to refresh the packed refs.
	 */
	if (error <= 0) {
		if (error == GIT_ENOTFOUND) {
			git_sortedcache_clear(backend->refcache, true);
			git_error_clear();
			error = 0;
		}
		return error;
	}

	/* At this point, refresh the packed refs from the loaded buffer. */

	git_sortedcache_clear(backend->refcache, false);

	scan = (char *)packedrefs.ptr;
	eof  = scan + packedrefs.size;

	backend->peeling_mode = PEELING_NONE;

	if (*scan == '#') {
		static const char *traits_header = "# pack-refs with: ";

		if (git__prefixcmp(scan, traits_header) == 0) {
			scan += strlen(traits_header);
			eol = strchr(scan, '\n');

			if (!eol)
				goto parse_failed;
			*eol = '\0';

			if (strstr(scan, " fully-peeled ") != NULL) {
				backend->peeling_mode = PEELING_FULL;
			} else if (strstr(scan, " peeled ") != NULL) {
				backend->peeling_mode = PEELING_STANDARD;
			}

			scan = eol + 1;
		}
	}

	while (scan < eof && *scan == '#') {
		if (!(eol = strchr(scan, '\n')))
			goto parse_failed;
		scan = eol + 1;
	}

	while (scan < eof) {
		struct packref *ref;
		git_oid oid;

		/* parse "<OID> <refname>\n" */

		if (git_oid_fromstr(&oid, scan) < 0)
			goto parse_failed;
		scan += GIT_OID_HEXSZ;

		if (*scan++ != ' ')
			goto parse_failed;
		if (!(eol = strchr(scan, '\n')))
			goto parse_failed;
		*eol = '\0';
		if (eol[-1] == '\r')
			eol[-1] = '\0';

		if (git_sortedcache_upsert((void **)&ref, backend->refcache, scan) < 0)
			goto parse_failed;
		scan = eol + 1;

		git_oid_cpy(&ref->oid, &oid);

		/* look for optional "^<OID>\n" */

		if (*scan == '^') {
			if (git_oid_fromstr(&oid, scan + 1) < 0)
				goto parse_failed;
			scan += GIT_OID_HEXSZ + 1;

			if (scan < eof) {
				if (!(eol = strchr(scan, '\n')))
					goto parse_failed;
				scan = eol + 1;
			}

			git_oid_cpy(&ref->peel, &oid);
			ref->flags |= PACKREF_HAS_PEEL;
		}
		else if (backend->peeling_mode == PEELING_FULL ||
				(backend->peeling_mode == PEELING_STANDARD &&
				 git__prefixcmp(ref->name, GIT_REFS_TAGS_DIR) == 0))
			ref->flags |= PACKREF_CANNOT_PEEL;
	}

	git_sortedcache_wunlock(backend->refcache);
	git_buf_dispose(&packedrefs);

	return 0;

parse_failed:
	git_error_set(GIT_ERROR_REFERENCE, "corrupted packed references file");

	git_sortedcache_clear(backend->refcache, false);
	git_sortedcache_wunlock(backend->refcache);
	git_buf_dispose(&packedrefs);

	return -1;
}