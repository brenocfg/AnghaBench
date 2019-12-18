#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_12__ {char const* original_repos_relpath; char const* changed_author; int op_depth; char const* target; int moved_here; int /*<<< orphan*/  const* conflict; int /*<<< orphan*/  const* work_items; int /*<<< orphan*/  original_repos_id; int /*<<< orphan*/  not_present_op_depth; int /*<<< orphan*/  changed_date; void* changed_rev; int /*<<< orphan*/  const* props; void* original_revnum; int /*<<< orphan*/  kind; int /*<<< orphan*/  presence; } ;
typedef  TYPE_2__ insert_working_baton_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  blank_iwb (TYPE_2__*) ; 
 int /*<<< orphan*/  create_repos_id (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_entries (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_working_node (TYPE_2__*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_depth_for_copy (int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,char const*,void*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_node_symlink ; 
 int /*<<< orphan*/  svn_wc__db_status_normal ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_copy_symlink(svn_wc__db_t *db,
                           const char *local_abspath,
                           const apr_hash_t *props,
                           svn_revnum_t changed_rev,
                           apr_time_t changed_date,
                           const char *changed_author,
                           const char *original_repos_relpath,
                           const char *original_root_url,
                           const char *original_uuid,
                           svn_revnum_t original_revision,
                           const char *target,
                           svn_boolean_t is_move,
                           const svn_skel_t *conflict,
                           const svn_skel_t *work_items,
                           apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  insert_working_baton_t iwb;
  int parent_op_depth;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(props != NULL);
  /* ### any assertions for CHANGED_* ?  */
  /* ### any assertions for ORIGINAL_* ?  */
  SVN_ERR_ASSERT(target != NULL);

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              local_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  blank_iwb(&iwb);

  iwb.presence = svn_wc__db_status_normal;
  iwb.kind = svn_node_symlink;


  if (original_root_url != NULL)
    {
      SVN_ERR(create_repos_id(&iwb.original_repos_id,
                              original_root_url, original_uuid,
                              wcroot->sdb, scratch_pool));
      iwb.original_repos_relpath = original_repos_relpath;
      iwb.original_revnum = original_revision;

      iwb.props = props;
      iwb.changed_rev = changed_rev;
      iwb.changed_date = changed_date;
      iwb.changed_author = changed_author;
    }

  /* ### Should we do this inside the transaction? */
  SVN_ERR(op_depth_for_copy(&iwb.op_depth, &iwb.not_present_op_depth,
                            &parent_op_depth, iwb.original_repos_id,
                            original_repos_relpath, original_revision,
                            wcroot, local_relpath, scratch_pool));

  iwb.target = target;
  iwb.moved_here = is_move && (parent_op_depth == 0 ||
                               iwb.op_depth == parent_op_depth);

  iwb.work_items = work_items;
  iwb.conflict = conflict;

  SVN_WC__DB_WITH_TXN(
            insert_working_node(&iwb, wcroot, local_relpath, scratch_pool),
            wcroot);
  SVN_ERR(flush_entries(wcroot, local_abspath, svn_depth_empty, scratch_pool));

  return SVN_NO_ERROR;
}