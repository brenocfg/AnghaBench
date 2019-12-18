#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* path; } ;
struct entry_internal {size_t pathlen; char* path; TYPE_2__ const entry; } ;
typedef  TYPE_2__ git_index_entry ;
struct TYPE_8__ {size_t length; struct entry_internal** contents; } ;
struct TYPE_10__ {TYPE_1__ entries; } ;
typedef  TYPE_3__ git_index ;

/* Variables and functions */
 int GIT_INDEX_ENTRY_STAGE (TYPE_2__ const*) ; 
 scalar_t__ index_remove_entry (TYPE_3__*,size_t) ; 
 scalar_t__ memcmp (char const*,char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int has_file_name(git_index *index,
	 const git_index_entry *entry, size_t pos, int ok_to_replace)
{
	size_t len = strlen(entry->path);
	int stage = GIT_INDEX_ENTRY_STAGE(entry);
	const char *name = entry->path;

	while (pos < index->entries.length) {
		struct entry_internal *p = index->entries.contents[pos++];

		if (len >= p->pathlen)
			break;
		if (memcmp(name, p->path, len))
			break;
		if (GIT_INDEX_ENTRY_STAGE(&p->entry) != stage)
			continue;
		if (p->path[len] != '/')
			continue;
		if (!ok_to_replace)
			return -1;

		if (index_remove_entry(index, --pos) < 0)
			break;
	}
	return 0;
}