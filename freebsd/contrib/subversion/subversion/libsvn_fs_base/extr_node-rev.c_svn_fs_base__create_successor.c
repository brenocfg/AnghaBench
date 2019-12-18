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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_bdb__new_successor_id (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__put_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__create_successor(const svn_fs_id_t **new_id_p,
                              svn_fs_t *fs,
                              const svn_fs_id_t *old_id,
                              node_revision_t *new_noderev,
                              const char *copy_id,
                              const char *txn_id,
                              trail_t *trail,
                              apr_pool_t *pool)
{
  svn_fs_id_t *new_id;

  /* Choose an ID for the new node, and store it in the database.  */
  SVN_ERR(svn_fs_bdb__new_successor_id(&new_id, fs, old_id, copy_id,
                                       txn_id, trail, pool));

  /* Store the new skel under that ID.  */
  SVN_ERR(svn_fs_bdb__put_node_revision(fs, new_id, new_noderev,
                                        trail, pool));

  *new_id_p = new_id;
  return SVN_NO_ERROR;
}