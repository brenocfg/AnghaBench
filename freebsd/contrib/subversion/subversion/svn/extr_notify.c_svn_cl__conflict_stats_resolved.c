#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_wc_conflict_kind_t ;
struct TYPE_3__ {int /*<<< orphan*/  tree_conflicts_resolved; int /*<<< orphan*/  tree_conflicts; int /*<<< orphan*/  prop_conflicts_resolved; int /*<<< orphan*/  prop_conflicts; int /*<<< orphan*/  text_conflicts_resolved; int /*<<< orphan*/  text_conflicts; } ;
typedef  TYPE_1__ svn_cl__conflict_stats_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
#define  svn_wc_conflict_kind_property 130 
#define  svn_wc_conflict_kind_text 129 
#define  svn_wc_conflict_kind_tree 128 

void
svn_cl__conflict_stats_resolved(svn_cl__conflict_stats_t *conflict_stats,
                                const char *path_local,
                                svn_wc_conflict_kind_t conflict_kind)
{
  switch (conflict_kind)
    {
      case svn_wc_conflict_kind_text:
        if (svn_hash_gets(conflict_stats->text_conflicts, path_local))
          {
            svn_hash_sets(conflict_stats->text_conflicts, path_local, NULL);
            conflict_stats->text_conflicts_resolved++;
          }
        break;
      case svn_wc_conflict_kind_property:
        if (svn_hash_gets(conflict_stats->prop_conflicts, path_local))
          {
            svn_hash_sets(conflict_stats->prop_conflicts, path_local, NULL);
            conflict_stats->prop_conflicts_resolved++;
          }
        break;
      case svn_wc_conflict_kind_tree:
        if (svn_hash_gets(conflict_stats->tree_conflicts, path_local))
          {
            svn_hash_sets(conflict_stats->tree_conflicts, path_local, NULL);
            conflict_stats->tree_conflicts_resolved++;
          }
        break;
    }
}