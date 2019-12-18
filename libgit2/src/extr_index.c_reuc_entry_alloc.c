#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
struct reuc_entry_internal {size_t pathlen; int /*<<< orphan*/  path; TYPE_1__ entry; } ;
typedef  int /*<<< orphan*/  git_index_reuc_entry ;

/* Variables and functions */
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,size_t,int) ; 
 struct reuc_entry_internal* git__calloc (int,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static git_index_reuc_entry *reuc_entry_alloc(const char *path)
{
	size_t pathlen = strlen(path),
		structlen = sizeof(struct reuc_entry_internal),
		alloclen;
	struct reuc_entry_internal *entry;

	if (GIT_ADD_SIZET_OVERFLOW(&alloclen, structlen, pathlen) ||
		GIT_ADD_SIZET_OVERFLOW(&alloclen, alloclen, 1))
		return NULL;

	entry = git__calloc(1, alloclen);
	if (!entry)
		return NULL;

	entry->pathlen = pathlen;
	memcpy(entry->path, path, pathlen);
	entry->entry.path = entry->path;

	return (git_index_reuc_entry *)entry;
}