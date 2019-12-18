#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
struct TYPE_7__ {int /*<<< orphan*/  node_kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 scalar_t__ SVN_NO_ERROR ; 
 scalar_t__ assert_tree_conflict (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* get_conflict_desc2_t (TYPE_1__*) ; 

svn_node_kind_t
svn_client_conflict_tree_get_victim_node_kind(svn_client_conflict_t *conflict)
{
  SVN_ERR_ASSERT_NO_RETURN(assert_tree_conflict(conflict, conflict->pool)
                           == SVN_NO_ERROR);

  return get_conflict_desc2_t(conflict)->node_kind;
}