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
struct name_entry {int /*<<< orphan*/  path; } ;
struct traverse_info {int pathlen; struct traverse_info* prev; struct name_entry name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int tree_entry_len (struct name_entry const*) ; 

char *make_traverse_path(char *path, const struct traverse_info *info, const struct name_entry *n)
{
	int len = tree_entry_len(n);
	int pathlen = info->pathlen;

	path[pathlen + len] = 0;
	for (;;) {
		memcpy(path + pathlen, n->path, len);
		if (!pathlen)
			break;
		path[--pathlen] = '/';
		n = &info->name;
		len = tree_entry_len(n);
		info = info->prev;
		pathlen -= len;
	}
	return path;
}