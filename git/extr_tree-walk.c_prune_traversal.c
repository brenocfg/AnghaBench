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
struct traverse_info {int /*<<< orphan*/  pathspec; } ;
struct strbuf {int dummy; } ;
struct name_entry {int dummy; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 int tree_entry_interesting (struct index_state*,struct name_entry*,struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int prune_traversal(struct index_state *istate,
				  struct name_entry *e,
				  struct traverse_info *info,
				  struct strbuf *base,
				  int still_interesting)
{
	if (!info->pathspec || still_interesting == 2)
		return 2;
	if (still_interesting < 0)
		return still_interesting;
	return tree_entry_interesting(istate, e, base,
				      0, info->pathspec);
}