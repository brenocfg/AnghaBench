#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_8__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_DIRECTORY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_node_revision (TYPE_1__**,TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_fs__rep_contents_dir_entry (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 

svn_error_t *
svn_fs_fs__dag_dir_entry(svn_fs_dirent_t **dirent,
                         dag_node_t *node,
                         const char* name,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  node_revision_t *noderev;
  SVN_ERR(get_node_revision(&noderev, node));

  if (noderev->kind != svn_node_dir)
    return svn_error_create(SVN_ERR_FS_NOT_DIRECTORY, NULL,
                            _("Can't get entries of non-directory"));

  /* Get a dirent hash for this directory. */
  return svn_fs_fs__rep_contents_dir_entry(dirent, node->fs, noderev, name,
                                           result_pool, scratch_pool);
}