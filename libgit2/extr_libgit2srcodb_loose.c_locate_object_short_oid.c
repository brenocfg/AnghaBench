#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {size_t short_oid_len; int found; scalar_t__ res_oid; void* dir_len; scalar_t__ short_oid; } ;
typedef  TYPE_1__ loose_locate_object_state ;
struct TYPE_15__ {char* objects_dir; } ;
typedef  TYPE_2__ loose_backend ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_16__ {char* ptr; int size; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 int GIT_EAMBIGUOUS ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  fn_locate_object_short_oid ; 
 scalar_t__ git_buf_grow (TYPE_3__*,size_t) ; 
 void* git_buf_len (TYPE_3__*) ; 
 scalar_t__ git_buf_put (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_3__*,char*,size_t) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_3__*,size_t) ; 
 int git_odb__error_ambiguous (char*) ; 
 int git_odb__error_notfound (char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/  const*) ; 
 int git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_oid_pathfmt (char*,int /*<<< orphan*/ *) ; 
 int git_path_direach (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_path_to_dir (TYPE_3__*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int locate_object_short_oid(
	git_buf *object_location,
	git_oid *res_oid,
	loose_backend *backend,
	const git_oid *short_oid,
	size_t len)
{
	char *objects_dir = backend->objects_dir;
	size_t dir_len = strlen(objects_dir), alloc_len;
	loose_locate_object_state state;
	int error;

	/* prealloc memory for OBJ_DIR/xx/xx..38x..xx */
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, dir_len, GIT_OID_HEXSZ);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, alloc_len, 3);
	if (git_buf_grow(object_location, alloc_len) < 0)
		return -1;

	git_buf_set(object_location, objects_dir, dir_len);
	git_path_to_dir(object_location);

	/* save adjusted position at end of dir so it can be restored later */
	dir_len = git_buf_len(object_location);

	/* Convert raw oid to hex formatted oid */
	git_oid_fmt((char *)state.short_oid, short_oid);

	/* Explore OBJ_DIR/xx/ where xx is the beginning of hex formatted short oid */
	if (git_buf_put(object_location, (char *)state.short_oid, 3) < 0)
		return -1;
	object_location->ptr[object_location->size - 1] = '/';

	/* Check that directory exists */
	if (git_path_isdir(object_location->ptr) == false)
		return git_odb__error_notfound("no matching loose object for prefix",
			short_oid, len);

	state.dir_len = git_buf_len(object_location);
	state.short_oid_len = len;
	state.found = 0;

	/* Explore directory to find a unique object matching short_oid */
	error = git_path_direach(
		object_location, 0, fn_locate_object_short_oid, &state);
	if (error < 0 && error != GIT_EAMBIGUOUS)
		return error;

	if (!state.found)
		return git_odb__error_notfound("no matching loose object for prefix",
			short_oid, len);

	if (state.found > 1)
		return git_odb__error_ambiguous("multiple matches in loose objects");

	/* Convert obtained hex formatted oid to raw */
	error = git_oid_fromstr(res_oid, (char *)state.res_oid);
	if (error)
		return error;

	/* Update the location according to the oid obtained */
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, dir_len, GIT_OID_HEXSZ);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, alloc_len, 2);

	git_buf_truncate(object_location, dir_len);
	if (git_buf_grow(object_location, alloc_len) < 0)
		return -1;

	git_oid_pathfmt(object_location->ptr + dir_len, res_oid);

	object_location->size += GIT_OID_HEXSZ + 1;
	object_location->ptr[object_location->size] = '\0';

	return 0;
}