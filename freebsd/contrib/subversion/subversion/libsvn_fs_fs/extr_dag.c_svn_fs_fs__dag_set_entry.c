#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_1__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * set_entry (TYPE_1__*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_check_mutable (TYPE_1__*) ; 
 scalar_t__ svn_node_dir ; 

svn_error_t *
svn_fs_fs__dag_set_entry(dag_node_t *node,
                         const char *entry_name,
                         const svn_fs_id_t *id,
                         svn_node_kind_t kind,
                         const svn_fs_fs__id_part_t *txn_id,
                         apr_pool_t *pool)
{
  /* Check it's a directory. */
  if (node->kind != svn_node_dir)
    return svn_error_create
      (SVN_ERR_FS_NOT_DIRECTORY, NULL,
       _("Attempted to set entry in non-directory node"));

  /* Check it's mutable. */
  if (! svn_fs_fs__dag_check_mutable(node))
    return svn_error_create
      (SVN_ERR_FS_NOT_MUTABLE, NULL,
       _("Attempted to set entry in immutable node"));

  return set_entry(node, entry_name, id, kind, txn_id, pool);
}