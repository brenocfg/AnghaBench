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
struct TYPE_8__ {size_t objects_dirlen; int /*<<< orphan*/  objects_dir; } ;
typedef  TYPE_1__ loose_backend ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_9__ {char* ptr; int size; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int GIT_OID_HEXSZ ; 
 scalar_t__ git_buf_grow (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_oid_pathfmt (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_path_to_dir (TYPE_2__*) ; 

__attribute__((used)) static int object_file_name(
	git_buf *name, const loose_backend *be, const git_oid *id)
{
	size_t alloclen;

	/* expand length for object root + 40 hex sha1 chars + 2 * '/' + '\0' */
	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, be->objects_dirlen, GIT_OID_HEXSZ);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, alloclen, 3);
	if (git_buf_grow(name, alloclen) < 0)
		return -1;

	git_buf_set(name, be->objects_dir, be->objects_dirlen);
	git_path_to_dir(name);

	/* loose object filename: aa/aaa... (41 bytes) */
	git_oid_pathfmt(name->ptr + name->size, id);
	name->size += GIT_OID_HEXSZ + 1;
	name->ptr[name->size] = '\0';

	return 0;
}