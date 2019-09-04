#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct tree_key_search {char const* filename; scalar_t__ filename_len; } ;
struct TYPE_9__ {size_t filename_len; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ git_tree_entry ;
struct TYPE_11__ {size_t size; } ;
struct TYPE_10__ {TYPE_5__ entries; } ;
typedef  TYPE_2__ git_tree ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  TREE_ENTRY_CHECK_NAMELEN (size_t) ; 
 TYPE_1__* git_array_get (TYPE_5__,size_t) ; 
 scalar_t__ git_array_search (size_t*,TYPE_5__,scalar_t__ (*) (struct tree_key_search*,TYPE_1__ const*),struct tree_key_search*) ; 
 scalar_t__ homing_search_cmp (struct tree_key_search*,TYPE_1__ const*) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int tree_key_search(
	size_t *at_pos,
	const git_tree *tree,
	const char *filename,
	size_t filename_len)
{
	struct tree_key_search ksearch;
	const git_tree_entry *entry;
	size_t homing, i;

	TREE_ENTRY_CHECK_NAMELEN(filename_len);

	ksearch.filename = filename;
	ksearch.filename_len = (uint16_t)filename_len;

	/* Initial homing search; find an entry on the tree with
	 * the same prefix as the filename we're looking for */

	if (git_array_search(&homing,
		tree->entries, &homing_search_cmp, &ksearch) < 0)
		return GIT_ENOTFOUND; /* just a signal error; not passed back to user */

	/* We found a common prefix. Look forward as long as
	 * there are entries that share the common prefix */
	for (i = homing; i < tree->entries.size; ++i) {
		entry = git_array_get(tree->entries, i);

		if (homing_search_cmp(&ksearch, entry) < 0)
			break;

		if (entry->filename_len == filename_len &&
			memcmp(filename, entry->filename, filename_len) == 0) {
			if (at_pos)
				*at_pos = i;

			return 0;
		}
	}

	/* If we haven't found our filename yet, look backwards
	 * too as long as we have entries with the same prefix */
	if (homing > 0) {
		i = homing - 1;

		do {
			entry = git_array_get(tree->entries, i);

			if (homing_search_cmp(&ksearch, entry) > 0)
				break;

			if (entry->filename_len == filename_len &&
				memcmp(filename, entry->filename, filename_len) == 0) {
				if (at_pos)
					*at_pos = i;

				return 0;
			}
		} while (i-- > 0);
	}

	/* The filename doesn't exist at all */
	return GIT_ENOTFOUND;
}