#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iterator_pathlist_search_t ;
typedef  int /*<<< orphan*/  git_vector_cmp ;
struct TYPE_7__ {scalar_t__ length; } ;
struct TYPE_6__ {scalar_t__ (* prefixcomp ) (char const*,char const*) ;TYPE_3__ pathlist; scalar_t__ strcomp; } ;
typedef  TYPE_1__ git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  ITERATOR_PATHLIST_FULL ; 
 int /*<<< orphan*/  ITERATOR_PATHLIST_IS_DIR ; 
 int /*<<< orphan*/  ITERATOR_PATHLIST_IS_FILE ; 
 int /*<<< orphan*/  ITERATOR_PATHLIST_IS_PARENT ; 
 int /*<<< orphan*/  ITERATOR_PATHLIST_NONE ; 
 int /*<<< orphan*/  assert (char const) ; 
 int git_vector_bsearch2 (size_t*,TYPE_3__*,int /*<<< orphan*/ ,char const*) ; 
 char* git_vector_get (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  git_vector_sort (TYPE_3__*) ; 
 scalar_t__ stub1 (char const*,char const*) ; 

__attribute__((used)) static iterator_pathlist_search_t iterator_pathlist_search(
	git_iterator *iter, const char *path, size_t path_len)
{
	const char *p;
	size_t idx;
	int error;

	if (iter->pathlist.length == 0)
		return ITERATOR_PATHLIST_FULL;

	git_vector_sort(&iter->pathlist);

	error = git_vector_bsearch2(&idx, &iter->pathlist,
		(git_vector_cmp)iter->strcomp, path);

	/* the given path was found in the pathlist.  since the pathlist only
	 * matches directories when they're suffixed with a '/', analyze the
	 * path string to determine whether it's a directory or not.
	 */
	if (error == 0) {
		if (path_len && path[path_len-1] == '/')
			return ITERATOR_PATHLIST_IS_DIR;

		return ITERATOR_PATHLIST_IS_FILE;
	}

	/* at this point, the path we're examining may be a directory (though we
	 * don't know that yet, since we're avoiding a stat unless it's necessary)
	 * so walk the pathlist looking for the given path with a '/' after it,
	 */
	while ((p = git_vector_get(&iter->pathlist, idx)) != NULL) {
		if (iter->prefixcomp(p, path) != 0)
			break;

		/* an exact match would have been matched by the bsearch above */
		assert(p[path_len]);

		/* is this a literal directory entry (eg `foo/`) or a file beneath */
		if (p[path_len] == '/') {
			return (p[path_len+1] == '\0') ?
				ITERATOR_PATHLIST_IS_DIR :
				ITERATOR_PATHLIST_IS_PARENT;
		}

		if (p[path_len] > '/')
			break;

		idx++;
	}

	return ITERATOR_PATHLIST_NONE;
}