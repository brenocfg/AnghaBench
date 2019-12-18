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
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  dir_entry_id_from_node (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_single_path_component (char const*) ; 

svn_error_t *
svn_fs_base__dag_open(dag_node_t **child_p,
                      dag_node_t *parent,
                      const char *name,
                      trail_t *trail,
                      apr_pool_t *pool)
{
  const svn_fs_id_t *node_id;

  /* Ensure that NAME exists in PARENT's entry list. */
  SVN_ERR(dir_entry_id_from_node(&node_id, parent, name, trail, pool));
  if (! node_id)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FOUND, NULL,
       _("Attempted to open non-existent child node '%s'"), name);

  /* Make sure that NAME is a single path component. */
  if (! svn_path_is_single_path_component(name))
    return svn_error_createf
      (SVN_ERR_FS_NOT_SINGLE_PATH_COMPONENT, NULL,
       _("Attempted to open node with an illegal name '%s'"), name);

  /* Now get the node that was requested. */
  return svn_fs_base__dag_get_node(child_p, svn_fs_base__dag_get_fs(parent),
                                   node_id, trail, pool);
}