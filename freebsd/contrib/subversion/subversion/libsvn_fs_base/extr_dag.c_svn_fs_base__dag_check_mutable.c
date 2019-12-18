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
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__id_txn_id (int /*<<< orphan*/ ) ; 

svn_boolean_t svn_fs_base__dag_check_mutable(dag_node_t *node,
                                             const char *txn_id)
{
  return (strcmp(svn_fs_base__id_txn_id(svn_fs_base__dag_get_id(node)),
                 txn_id) == 0);
}