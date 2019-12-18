#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct insert_base_baton_t {scalar_t__ kind; scalar_t__ repos_id; int /*<<< orphan*/  file_external; int /*<<< orphan*/  work_items; int /*<<< orphan*/  keep_recorded_info; int /*<<< orphan*/  new_actual_props; int /*<<< orphan*/  update_actual_props; int /*<<< orphan*/  conflict; int /*<<< orphan*/  target; int /*<<< orphan*/  checksum; int /*<<< orphan*/  dav_cache; int /*<<< orphan*/  changed_author; int /*<<< orphan*/  changed_date; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  iprops; int /*<<< orphan*/  props; int /*<<< orphan*/  revision; int /*<<< orphan*/  repos_relpath; scalar_t__ status; } ;
struct TYPE_17__ {scalar_t__ repos_id; scalar_t__ kind; scalar_t__ presence; int /*<<< orphan*/  recorded_revision; int /*<<< orphan*/  recorded_peg_revision; int /*<<< orphan*/  recorded_repos_relpath; int /*<<< orphan*/  record_ancestor_relpath; int /*<<< orphan*/  work_items; int /*<<< orphan*/  keep_recorded_info; int /*<<< orphan*/  new_actual_props; int /*<<< orphan*/  update_actual_props; int /*<<< orphan*/  conflict; int /*<<< orphan*/  target; int /*<<< orphan*/  checksum; int /*<<< orphan*/  dav_cache; int /*<<< orphan*/  changed_author; int /*<<< orphan*/  changed_date; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  iprops; int /*<<< orphan*/  props; int /*<<< orphan*/  revision; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; } ;
typedef  TYPE_3__ insert_external_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 scalar_t__ INVALID_REPOS_ID ; 
 int /*<<< orphan*/  STMT_INSERT_EXTERNAL ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blank_ibb (struct insert_base_baton_t*) ; 
 int /*<<< orphan*/  create_repos_id (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_base_node (struct insert_base_baton_t*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 
 int /*<<< orphan*/  svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_revnum (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_base_get_info_internal (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_normal ; 

__attribute__((used)) static svn_error_t *
insert_external_node(const insert_external_baton_t *ieb,
                     svn_wc__db_wcroot_t *wcroot,
                     const char *local_relpath,
                     apr_pool_t *scratch_pool)
{
  svn_wc__db_status_t status;
  svn_error_t *err;
  svn_boolean_t update_root;
  apr_int64_t repos_id;
  svn_sqlite__stmt_t *stmt;

  if (ieb->repos_id != INVALID_REPOS_ID)
    repos_id = ieb->repos_id;
  else
    SVN_ERR(create_repos_id(&repos_id, ieb->repos_root_url, ieb->repos_uuid,
                            wcroot->sdb, scratch_pool));

  /* And there must be no existing BASE node or it must be a file external */
  err = svn_wc__db_base_get_info_internal(&status, NULL, NULL, NULL, NULL,
                                          NULL, NULL, NULL, NULL, NULL,
                                          NULL, NULL, NULL, NULL, &update_root,
                                          wcroot, local_relpath,
                                          scratch_pool, scratch_pool);
  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      svn_error_clear(err);
    }
  else if (status == svn_wc__db_status_normal && !update_root)
    return svn_error_create(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL, NULL);

  if (ieb->kind == svn_node_file
      || ieb->kind == svn_node_symlink)
    {
      struct insert_base_baton_t ibb;

      blank_ibb(&ibb);

      ibb.status          = svn_wc__db_status_normal;
      ibb.kind            = ieb->kind;

      ibb.repos_id        = repos_id;
      ibb.repos_relpath   = ieb->repos_relpath;
      ibb.revision        = ieb->revision;

      ibb.props           = ieb->props;
      ibb.iprops          = ieb->iprops;
      ibb.changed_rev     = ieb->changed_rev;
      ibb.changed_date    = ieb->changed_date;
      ibb.changed_author  = ieb->changed_author;

      ibb.dav_cache       = ieb->dav_cache;

      ibb.checksum        = ieb->checksum;
      ibb.target          = ieb->target;

      ibb.conflict        = ieb->conflict;

      ibb.update_actual_props = ieb->update_actual_props;
      ibb.new_actual_props    = ieb->new_actual_props;

      ibb.keep_recorded_info  = ieb->keep_recorded_info;

      ibb.work_items      = ieb->work_items;

      ibb.file_external = TRUE;

      SVN_ERR(insert_base_node(&ibb, wcroot, local_relpath, scratch_pool));
    }
  else
    SVN_ERR(add_work_items(wcroot->sdb, ieb->work_items, scratch_pool));

  /* The externals table only support presence normal and excluded */
  SVN_ERR_ASSERT(ieb->presence == svn_wc__db_status_normal
                 || ieb->presence == svn_wc__db_status_excluded);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb, STMT_INSERT_EXTERNAL));

  SVN_ERR(svn_sqlite__bindf(stmt, "issttsis",
                            wcroot->wc_id,
                            local_relpath,
                            svn_relpath_dirname(local_relpath,
                                                scratch_pool),
                            presence_map, ieb->presence,
                            kind_map, ieb->kind,
                            ieb->record_ancestor_relpath,
                            repos_id,
                            ieb->recorded_repos_relpath));

  if (SVN_IS_VALID_REVNUM(ieb->recorded_peg_revision))
    SVN_ERR(svn_sqlite__bind_revnum(stmt, 9, ieb->recorded_peg_revision));

  if (SVN_IS_VALID_REVNUM(ieb->recorded_revision))
    SVN_ERR(svn_sqlite__bind_revnum(stmt, 10, ieb->recorded_revision));

  SVN_ERR(svn_sqlite__insert(NULL, stmt));

  return SVN_NO_ERROR;
}