#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {char* filename; scalar_t__ filename_len; void* oid; } ;
typedef  TYPE_1__ git_tree_entry ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,size_t,int) ; 
 int GIT_OID_RAWSZ ; 
 int /*<<< orphan*/  TREE_ENTRY_CHECK_NAMELEN (size_t) ; 
 TYPE_1__* git__calloc (int,size_t) ; 
 int /*<<< orphan*/  git_oid_cpy (void*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static git_tree_entry *alloc_entry(const char *filename, size_t filename_len, const git_oid *id)
{
	git_tree_entry *entry = NULL;
	size_t tree_len;

	TREE_ENTRY_CHECK_NAMELEN(filename_len);

	if (GIT_ADD_SIZET_OVERFLOW(&tree_len, sizeof(git_tree_entry), filename_len) ||
	    GIT_ADD_SIZET_OVERFLOW(&tree_len, tree_len, 1) ||
	    GIT_ADD_SIZET_OVERFLOW(&tree_len, tree_len, GIT_OID_RAWSZ))
		return NULL;

	entry = git__calloc(1, tree_len);
	if (!entry)
		return NULL;

	{
		char *filename_ptr;
		void *id_ptr;

		filename_ptr = ((char *) entry) + sizeof(git_tree_entry);
		memcpy(filename_ptr, filename, filename_len);
		entry->filename = filename_ptr;

		id_ptr = filename_ptr + filename_len + 1;
		git_oid_cpy(id_ptr, id);
		entry->oid = id_ptr;
	}

	entry->filename_len = (uint16_t)filename_len;

	return entry;
}