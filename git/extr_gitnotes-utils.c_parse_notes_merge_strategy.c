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
typedef  enum notes_merge_strategy { ____Placeholder_notes_merge_strategy } notes_merge_strategy ;

/* Variables and functions */
 int NOTES_MERGE_RESOLVE_CAT_SORT_UNIQ ; 
 int NOTES_MERGE_RESOLVE_MANUAL ; 
 int NOTES_MERGE_RESOLVE_OURS ; 
 int NOTES_MERGE_RESOLVE_THEIRS ; 
 int NOTES_MERGE_RESOLVE_UNION ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int parse_notes_merge_strategy(const char *v, enum notes_merge_strategy *s)
{
	if (!strcmp(v, "manual"))
		*s = NOTES_MERGE_RESOLVE_MANUAL;
	else if (!strcmp(v, "ours"))
		*s = NOTES_MERGE_RESOLVE_OURS;
	else if (!strcmp(v, "theirs"))
		*s = NOTES_MERGE_RESOLVE_THEIRS;
	else if (!strcmp(v, "union"))
		*s = NOTES_MERGE_RESOLVE_UNION;
	else if (!strcmp(v, "cat_sort_uniq"))
		*s = NOTES_MERGE_RESOLVE_CAT_SORT_UNIQ;
	else
		return -1;

	return 0;
}