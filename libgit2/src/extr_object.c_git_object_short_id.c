#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int* id; TYPE_1__ member_0; } ;
typedef  TYPE_4__ git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_15__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {TYPE_2__ oid; } ;
struct TYPE_18__ {TYPE_3__ cached; } ;
typedef  TYPE_5__ git_object ;
struct TYPE_19__ {int size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_6__ git_buf ;

/* Variables and functions */
 int GIT_ABBREV_DEFAULT ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_ABBREV ; 
 int GIT_EAMBIGUOUS ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_buf_grow (TYPE_6__*,int) ; 
 int /*<<< orphan*/  git_buf_sanitize (TYPE_6__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/ * git_object_owner (TYPE_5__ const*) ; 
 int git_odb_exists_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_tostr (int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 int git_repository__configmap_lookup (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int**,int /*<<< orphan*/ *,int) ; 

int git_object_short_id(git_buf *out, const git_object *obj)
{
	git_repository *repo;
	int len = GIT_ABBREV_DEFAULT, error;
	git_oid id = {{0}};
	git_odb *odb;

	assert(out && obj);

	git_buf_sanitize(out);
	repo = git_object_owner(obj);

	if ((error = git_repository__configmap_lookup(&len, repo, GIT_CONFIGMAP_ABBREV)) < 0)
		return error;

	if ((error = git_repository_odb(&odb, repo)) < 0)
		return error;

	while (len < GIT_OID_HEXSZ) {
		/* set up short oid */
		memcpy(&id.id, &obj->cached.oid.id, (len + 1) / 2);
		if (len & 1)
			id.id[len / 2] &= 0xf0;

		error = git_odb_exists_prefix(NULL, odb, &id, len);
		if (error != GIT_EAMBIGUOUS)
			break;

		git_error_clear();
		len++;
	}

	if (!error && !(error = git_buf_grow(out, len + 1))) {
		git_oid_tostr(out->ptr, len + 1, &id);
		out->size = len;
	}

	git_odb_free(odb);

	return error;
}