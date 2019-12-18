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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs_fs__dag_get_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_is_txn (int /*<<< orphan*/ ) ; 

svn_boolean_t svn_fs_fs__dag_check_mutable(const dag_node_t *node)
{
  return svn_fs_fs__id_is_txn(svn_fs_fs__dag_get_id(node));
}