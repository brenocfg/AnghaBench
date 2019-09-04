#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_5__ {char const* filename; int /*<<< orphan*/ * oid; void* filename_len; void* attr; } ;
typedef  TYPE_1__ git_tree_entry ;
struct TYPE_6__ {int /*<<< orphan*/  entries; int /*<<< orphan*/ * odb_obj; } ;
typedef  TYPE_2__ git_tree ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TREE_SIZE ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ARRAY (int /*<<< orphan*/ ) ; 
 int GIT_OID_RAWSZ ; 
 size_t UINT16_MAX ; 
 TYPE_1__* git_array_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_array_init_to_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* memchr (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_mode (void**,char const*,int,char const**) ; 
 int tree_error (char*,int /*<<< orphan*/ *) ; 

int git_tree__parse_raw(void *_tree, const char *data, size_t size)
{
	git_tree *tree = _tree;
	const char *buffer;
	const char *buffer_end;

	buffer = data;
	buffer_end = buffer + size;

	tree->odb_obj = NULL;
	git_array_init_to_size(tree->entries, DEFAULT_TREE_SIZE);
	GIT_ERROR_CHECK_ARRAY(tree->entries);

	while (buffer < buffer_end) {
		git_tree_entry *entry;
		size_t filename_len;
		const char *nul;
		uint16_t attr;

		if (parse_mode(&attr, buffer, buffer_end - buffer, &buffer) < 0 || !buffer)
			return tree_error("failed to parse tree: can't parse filemode", NULL);

		if (buffer >= buffer_end || (*buffer++) != ' ')
			return tree_error("failed to parse tree: missing space after filemode", NULL);

		if ((nul = memchr(buffer, 0, buffer_end - buffer)) == NULL)
			return tree_error("failed to parse tree: object is corrupted", NULL);

		if ((filename_len = nul - buffer) == 0 || filename_len > UINT16_MAX)
			return tree_error("failed to parse tree: can't parse filename", NULL);

		if ((buffer_end - (nul + 1)) < GIT_OID_RAWSZ)
			return tree_error("failed to parse tree: can't parse OID", NULL);

		/* Allocate the entry */
		{
			entry = git_array_alloc(tree->entries);
			GIT_ERROR_CHECK_ALLOC(entry);

			entry->attr = attr;
			entry->filename_len = (uint16_t)filename_len;
			entry->filename = buffer;
			entry->oid = (git_oid *) ((char *) buffer + filename_len + 1);
		}

		buffer += filename_len + 1;
		buffer += GIT_OID_RAWSZ;
	}

	return 0;
}