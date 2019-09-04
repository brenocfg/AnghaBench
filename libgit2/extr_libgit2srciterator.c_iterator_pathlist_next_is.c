#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t length; char** contents; } ;
struct TYPE_4__ {size_t pathlist_walk_idx; int (* strncomp ) (char*,char const*,size_t) ;TYPE_3__ pathlist; } ;
typedef  TYPE_1__ git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  git_vector_sort (TYPE_3__*) ; 
 size_t min (size_t,size_t) ; 
 size_t strlen (char const*) ; 
 int stub1 (char*,char const*,size_t) ; 

__attribute__((used)) static bool iterator_pathlist_next_is(git_iterator *iter, const char *path)
{
	char *p;
	size_t path_len, p_len, cmp_len, i;
	int cmp;

	if (iter->pathlist.length == 0)
		return true;

	git_vector_sort(&iter->pathlist);

	path_len = strlen(path);

	/* for comparison, drop the trailing slash on the current '/' */
	if (path_len && path[path_len-1] == '/')
		path_len--;

	for (i = iter->pathlist_walk_idx; i < iter->pathlist.length; i++) {
		p = iter->pathlist.contents[i];
		p_len = strlen(p);

		if (p_len && p[p_len-1] == '/')
			p_len--;

		cmp_len = min(path_len, p_len);

		/* see if the pathlist entry is a prefix of this path */
		cmp = iter->strncomp(p, path, cmp_len);

		/* prefix match - see if there's an exact match, or if we were
		 * given a path that matches the directory
		 */
		if (cmp == 0) {
			/* if this pathlist entry is not suffixed with a '/' then
			 * it matches a path that is a file or a directory.
			 * (eg, pathlist = "foo" and path is "foo" or "foo/" or
			 * "foo/something")
			 */
			if (p[cmp_len] == '\0' &&
				(path[cmp_len] == '\0' || path[cmp_len] == '/'))
				return true;

			/* if this pathlist entry _is_ suffixed with a '/' then
			 * it matches only paths that are directories.
			 * (eg, pathlist = "foo/" and path is "foo/" or "foo/something")
			 */
			if (p[cmp_len] == '/' && path[cmp_len] == '/')
				return true;
		}

		/* this pathlist entry sorts before the given path, try the next */
		else if (cmp < 0) {
			iter->pathlist_walk_idx++;
			continue;
		}

		/* this pathlist sorts after the given path, no match. */
		else if (cmp > 0) {
			break;
		}
	}

	return false;
}