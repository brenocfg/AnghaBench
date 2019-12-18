#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ git_indexer ;
struct TYPE_11__ {char* ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 scalar_t__ GIT_OID_HEXSZ ; 
 scalar_t__ git_buf_grow (TYPE_2__*,scalar_t__) ; 
 int git_buf_len (TYPE_2__*) ; 
 scalar_t__ git_buf_oom (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int index_path(git_buf *path, git_indexer *idx, const char *suffix)
{
	const char prefix[] = "pack-";
	size_t slash = (size_t)path->size;

	/* search backwards for '/' */
	while (slash > 0 && path->ptr[slash - 1] != '/')
		slash--;

	if (git_buf_grow(path, slash + 1 + strlen(prefix) +
					 GIT_OID_HEXSZ + strlen(suffix) + 1) < 0)
		return -1;

	git_buf_truncate(path, slash);
	git_buf_puts(path, prefix);
	git_oid_fmt(path->ptr + git_buf_len(path), &idx->hash);
	path->size += GIT_OID_HEXSZ;
	git_buf_puts(path, suffix);

	return git_buf_oom(path) ? -1 : 0;
}