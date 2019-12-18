#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 size_t git_index_entrycount (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t find_next_dir(const char *dirname, git_index *index, size_t start)
{
	size_t dirlen, i, entries = git_index_entrycount(index);

	dirlen = strlen(dirname);
	for (i = start; i < entries; ++i) {
		const git_index_entry *entry = git_index_get_byindex(index, i);
		if (strlen(entry->path) < dirlen ||
		    memcmp(entry->path, dirname, dirlen) ||
			(dirlen > 0 && entry->path[dirlen] != '/')) {
			break;
		}
	}

	return i;
}