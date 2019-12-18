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
typedef  int /*<<< orphan*/  svn_fs_node_relation_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;

/* Variables and functions */
 scalar_t__ svn_fs_base__id_check_related (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ svn_fs_base__id_eq (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_node_common_ancestor ; 
 int /*<<< orphan*/  svn_fs_node_unchanged ; 
 int /*<<< orphan*/  svn_fs_node_unrelated ; 

svn_fs_node_relation_t
svn_fs_base__id_compare(const svn_fs_id_t *a,
                        const svn_fs_id_t *b)
{
  if (svn_fs_base__id_eq(a, b))
    return svn_fs_node_unchanged;
  return (svn_fs_base__id_check_related(a, b) ? svn_fs_node_common_ancestor
                                              : svn_fs_node_unrelated);
}