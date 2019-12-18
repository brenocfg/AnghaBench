#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_pool ;
struct TYPE_5__ {char* fullpath; char* path; } ;
typedef  TYPE_1__ git_attr_file_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 scalar_t__ git_path_root (char const*) ; 
 TYPE_1__* git_pool_mallocz (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int git_attr_cache__alloc_file_entry(
	git_attr_file_entry **out,
	const char *base,
	const char *path,
	git_pool *pool)
{
	size_t baselen = 0, pathlen = strlen(path);
	size_t cachesize = sizeof(git_attr_file_entry) + pathlen + 1;
	git_attr_file_entry *ce;

	if (base != NULL && git_path_root(path) < 0) {
		baselen = strlen(base);
		cachesize += baselen;

		if (baselen && base[baselen - 1] != '/')
			cachesize++;
	}

	ce = git_pool_mallocz(pool, cachesize);
	GIT_ERROR_CHECK_ALLOC(ce);

	if (baselen) {
		memcpy(ce->fullpath, base, baselen);

		if (base[baselen - 1] != '/')
			ce->fullpath[baselen++] = '/';
	}
	memcpy(&ce->fullpath[baselen], path, pathlen);

	ce->path = &ce->fullpath[baselen];
	*out = ce;

	return 0;
}