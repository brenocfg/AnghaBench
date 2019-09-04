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
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REALLOC_ARRAY (struct commit**,int) ; 
 struct commit** indexed_commits ; 
 int indexed_commits_alloc ; 
 int indexed_commits_nr ; 

__attribute__((used)) static void index_commit_for_bitmap(struct commit *commit)
{
	if (indexed_commits_nr >= indexed_commits_alloc) {
		indexed_commits_alloc = (indexed_commits_alloc + 32) * 2;
		REALLOC_ARRAY(indexed_commits, indexed_commits_alloc);
	}

	indexed_commits[indexed_commits_nr++] = commit;
}