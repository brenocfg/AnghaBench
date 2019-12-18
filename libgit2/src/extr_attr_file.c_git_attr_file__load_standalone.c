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
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_11__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ git_attr_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_FILE ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int git_attr_cache__alloc_file_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_attr_file__free (TYPE_2__*) ; 
 int git_attr_file__new (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_attr_file__parse_buffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_futils_readbuffer (TYPE_1__*,char const*) ; 

int git_attr_file__load_standalone(git_attr_file **out, const char *path)
{
	git_buf content = GIT_BUF_INIT;
	git_attr_file *file = NULL;
	int error;

	if ((error = git_futils_readbuffer(&content, path)) < 0)
		goto out;

	/*
	 * Because the cache entry is allocated from the file's own pool, we
	 * don't have to free it - freeing file+pool will free cache entry, too.
	 */

	if ((error = git_attr_file__new(&file, NULL, GIT_ATTR_FILE__FROM_FILE)) < 0 ||
	    (error = git_attr_file__parse_buffer(NULL, file, content.ptr, true)) < 0 ||
	    (error = git_attr_cache__alloc_file_entry(&file->entry, NULL, path, &file->pool)) < 0)
		goto out;

	*out = file;
out:
	if (error < 0)
		git_attr_file__free(file);
	git_buf_dispose(&content);

	return error;
}