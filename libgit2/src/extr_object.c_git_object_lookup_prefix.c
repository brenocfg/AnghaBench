#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  objects; } ;
typedef  TYPE_3__ git_repository ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_23__ {TYPE_2__ member_0; } ;
typedef  TYPE_4__ git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  scalar_t__ git_object_t ;
struct TYPE_20__ {scalar_t__ type; } ;
struct TYPE_24__ {TYPE_1__ cached; } ;
typedef  TYPE_5__ git_object ;
struct TYPE_25__ {scalar_t__ flags; } ;
typedef  TYPE_6__ git_cached_obj ;

/* Variables and functions */
 scalar_t__ GIT_CACHE_STORE_PARSED ; 
 scalar_t__ GIT_CACHE_STORE_RAW ; 
 int GIT_EAMBIGUOUS ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 scalar_t__ GIT_OBJECT_ANY ; 
 size_t GIT_OID_HEXSZ ; 
 size_t GIT_OID_MINPREFIXLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__* git_cache_get_any (int /*<<< orphan*/ *,TYPE_4__ const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_object__from_odb_object (TYPE_5__**,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  git_object_free (TYPE_5__*) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_4__ const*) ; 
 int git_odb_read_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  git_oid__cpy_prefix (TYPE_4__*,TYPE_4__ const*,size_t) ; 
 int git_repository_odb__weakptr (int /*<<< orphan*/ **,TYPE_3__*) ; 

int git_object_lookup_prefix(
	git_object **object_out,
	git_repository *repo,
	const git_oid *id,
	size_t len,
	git_object_t type)
{
	git_object *object = NULL;
	git_odb *odb = NULL;
	git_odb_object *odb_obj = NULL;
	int error = 0;

	assert(repo && object_out && id);

	if (len < GIT_OID_MINPREFIXLEN) {
		git_error_set(GIT_ERROR_OBJECT, "ambiguous lookup - OID prefix is too short");
		return GIT_EAMBIGUOUS;
	}

	error = git_repository_odb__weakptr(&odb, repo);
	if (error < 0)
		return error;

	if (len > GIT_OID_HEXSZ)
		len = GIT_OID_HEXSZ;

	if (len == GIT_OID_HEXSZ) {
		git_cached_obj *cached = NULL;

		/* We want to match the full id : we can first look up in the cache,
		 * since there is no need to check for non ambiguousity
		 */
		cached = git_cache_get_any(&repo->objects, id);
		if (cached != NULL) {
			if (cached->flags == GIT_CACHE_STORE_PARSED) {
				object = (git_object *)cached;

				if (type != GIT_OBJECT_ANY && type != object->cached.type) {
					git_object_free(object);
					git_error_set(GIT_ERROR_INVALID,
						"the requested type does not match the type in ODB");
					return GIT_ENOTFOUND;
				}

				*object_out = object;
				return 0;
			} else if (cached->flags == GIT_CACHE_STORE_RAW) {
				odb_obj = (git_odb_object *)cached;
			} else {
				assert(!"Wrong caching type in the global object cache");
			}
		} else {
			/* Object was not found in the cache, let's explore the backends.
			 * We could just use git_odb_read_unique_short_oid,
			 * it is the same cost for packed and loose object backends,
			 * but it may be much more costly for sqlite and hiredis.
			 */
			error = git_odb_read(&odb_obj, odb, id);
		}
	} else {
		git_oid short_oid = {{ 0 }};

		git_oid__cpy_prefix(&short_oid, id, len);

		/* If len < GIT_OID_HEXSZ (a strict short oid was given), we have
		 * 2 options :
		 * - We always search in the cache first. If we find that short oid is
		 *	ambiguous, we can stop. But in all the other cases, we must then
		 *	explore all the backends (to find an object if there was match,
		 *	or to check that oid is not ambiguous if we have found 1 match in
		 *	the cache)
		 * - We never explore the cache, go right to exploring the backends
		 * We chose the latter : we explore directly the backends.
		 */
		error = git_odb_read_prefix(&odb_obj, odb, &short_oid, len);
	}

	if (error < 0)
		return error;

	error = git_object__from_odb_object(object_out, repo, odb_obj, type);

	git_odb_object_free(odb_obj);

	return error;
}