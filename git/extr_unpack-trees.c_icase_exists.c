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
struct unpack_trees_options {int /*<<< orphan*/  src_index; } ;
struct stat {int dummy; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int CE_MATCH_IGNORE_SKIP_WORKTREE ; 
 int CE_MATCH_IGNORE_VALID ; 
 int /*<<< orphan*/  ie_match_stat (int /*<<< orphan*/ ,struct cache_entry const*,struct stat*,int) ; 
 struct cache_entry* index_file_exists (int /*<<< orphan*/ ,char const*,int,int) ; 

__attribute__((used)) static int icase_exists(struct unpack_trees_options *o, const char *name, int len, struct stat *st)
{
	const struct cache_entry *src;

	src = index_file_exists(o->src_index, name, len, 1);
	return src && !ie_match_stat(o->src_index, src, st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
}