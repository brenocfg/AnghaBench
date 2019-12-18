#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t length; } ;
struct pack_backend {TYPE_3__ packs; } ;
struct git_pack_file {int /*<<< orphan*/  pack_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 scalar_t__ git__suffixcmp (char const*,char*) ; 
 char* git_buf_cstr (TYPE_1__*) ; 
 size_t git_buf_len (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_mwindow_get_pack (struct git_pack_file**,int /*<<< orphan*/ ) ; 
 struct git_pack_file* git_vector_get (TYPE_3__*,size_t) ; 
 int git_vector_insert (TYPE_3__*,struct git_pack_file*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int packfile_load__cb(void *data, git_buf *path)
{
	struct pack_backend *backend = data;
	struct git_pack_file *pack;
	const char *path_str = git_buf_cstr(path);
	size_t i, cmp_len = git_buf_len(path);
	int error;

	if (cmp_len <= strlen(".idx") || git__suffixcmp(path_str, ".idx") != 0)
		return 0; /* not an index */

	cmp_len -= strlen(".idx");

	for (i = 0; i < backend->packs.length; ++i) {
		struct git_pack_file *p = git_vector_get(&backend->packs, i);

		if (strncmp(p->pack_name, path_str, cmp_len) == 0)
			return 0;
	}

	error = git_mwindow_get_pack(&pack, path->ptr);

	/* ignore missing .pack file as git does */
	if (error == GIT_ENOTFOUND) {
		git_error_clear();
		return 0;
	}

	if (!error)
		error = git_vector_insert(&backend->packs, pack);

	return error;

}