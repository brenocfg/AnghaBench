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
struct entry_srch_key {size_t pathlen; scalar_t__ stage; int /*<<< orphan*/  path; } ;
struct entry_internal {size_t pathlen; int /*<<< orphan*/  entry; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int GIT_INDEX_ENTRY_STAGE (int /*<<< orphan*/ *) ; 
 scalar_t__ GIT_INDEX_STAGE_ANY ; 
 int strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int git_index_entry_isrch(const void *key, const void *array_member)
{
	const struct entry_srch_key *srch_key = key;
	const struct entry_internal *entry = array_member;
	int cmp;
	size_t len1, len2, len;

	len1 = srch_key->pathlen;
	len2 = entry->pathlen;
	len = len1 < len2 ? len1 : len2;

	cmp = strncasecmp(srch_key->path, entry->path, len);

	if (cmp)
		return cmp;
	if (len1 < len2)
		return -1;
	if (len1 > len2)
		return 1;

	if (srch_key->stage != GIT_INDEX_STAGE_ANY)
		return srch_key->stage - GIT_INDEX_ENTRY_STAGE(&entry->entry);

	return 0;
}