#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct traverse_info {char* name; size_t namelen; struct traverse_info* prev; int /*<<< orphan*/  pathlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t st_add (int /*<<< orphan*/ ,size_t) ; 

char *make_traverse_path(char *path, size_t pathlen,
			 const struct traverse_info *info,
			 const char *name, size_t namelen)
{
	/* Always points to the end of the name we're about to add */
	size_t pos = st_add(info->pathlen, namelen);

	if (pos >= pathlen)
		BUG("too small buffer passed to make_traverse_path");

	path[pos] = 0;
	for (;;) {
		if (pos < namelen)
			BUG("traverse_info pathlen does not match strings");
		pos -= namelen;
		memcpy(path + pos, name, namelen);

		if (!pos)
			break;
		path[--pos] = '/';

		if (!info)
			BUG("traverse_info ran out of list items");
		name = info->name;
		namelen = info->namelen;
		info = info->prev;
	}
	return path;
}