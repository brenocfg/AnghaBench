#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  wc_id; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 scalar_t__ INVALID_REPOS_ID ; 
 int /*<<< orphan*/  STMT_RECURSIVE_UPDATE_NODE_REPO ; 
 int /*<<< orphan*/  STMT_UPDATE_LOCK_REPOS_ID ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  create_repos_id (scalar_t__*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_addition (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_deletion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_fetch_repos_info (int /*<<< orphan*/ *,char const**,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_excluded ; 

__attribute__((used)) static svn_error_t *
relocate_txn(svn_wc__db_wcroot_t *wcroot,
             const char *local_relpath,
             const char *repos_root_url,
             apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  apr_int64_t new_repos_id;
  const char *local_dir_relpath;
  svn_wc__db_status_t status;
  const char *repos_uuid;
  svn_boolean_t have_base_node;
  apr_int64_t old_repos_id;

  local_dir_relpath = local_relpath;

  SVN_ERR(read_info(&status,
                    NULL, NULL, NULL, &old_repos_id,
                    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                    NULL,
                    &have_base_node, NULL, NULL,
                    wcroot, local_relpath,
                    scratch_pool, scratch_pool));

  if (status == svn_wc__db_status_excluded)
    {
      /* The parent cannot be excluded, so look at the parent and then
         adjust the relpath */
      const char *parent_relpath = svn_relpath_dirname(local_dir_relpath,
                                                       scratch_pool);
      SVN_ERR(read_info(&status,
                        NULL, NULL, NULL, &old_repos_id,
                        NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                        NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                        NULL, NULL, NULL,
                        NULL, NULL, NULL,
                        wcroot, parent_relpath,
                        scratch_pool, scratch_pool));
      local_dir_relpath = parent_relpath;
    }

  if (old_repos_id == INVALID_REPOS_ID)
    {
      /* Do we need to support relocating something that is
         added/deleted/excluded without relocating the parent?  If not
         then perhaps relpath, root_url and uuid should be passed down
         to the children so that they don't have to scan? */

      if (status == svn_wc__db_status_deleted)
        {
          const char *work_del_relpath;

          SVN_ERR(scan_deletion(NULL, NULL,
                                &work_del_relpath, NULL,
                                wcroot, local_dir_relpath,
                                scratch_pool,
                                scratch_pool));
          if (work_del_relpath)
            {
              /* Deleted within a copy/move */

              /* The parent of the delete is added. */
              status = svn_wc__db_status_added;
              local_dir_relpath = svn_relpath_dirname(work_del_relpath,
                                                      scratch_pool);
            }
        }

      if (status == svn_wc__db_status_added)
        {
          SVN_ERR(scan_addition(NULL, NULL, NULL, &old_repos_id,
                                NULL, NULL, NULL, NULL, NULL, NULL,
                                wcroot, local_dir_relpath,
                                scratch_pool, scratch_pool));
        }
      else
        SVN_ERR(svn_wc__db_base_get_info_internal(NULL, NULL, NULL, NULL,
                                                  &old_repos_id,
                                                  NULL, NULL, NULL, NULL, NULL,
                                                  NULL, NULL, NULL, NULL, NULL,
                                                  wcroot, local_dir_relpath,
                                                  scratch_pool, scratch_pool));
    }

  SVN_ERR(svn_wc__db_fetch_repos_info(NULL, &repos_uuid, wcroot,
                                      old_repos_id, scratch_pool));
  SVN_ERR_ASSERT(repos_uuid);

  /* This function affects all the children of the given local_relpath,
     but the way that it does this is through the repos inheritance mechanism.
     So, we only need to rewrite the repos_id of the given local_relpath,
     as well as any children with a non-null repos_id, as well as various
     repos_id fields in the locks and working_node tables.
   */

  /* Get the repos_id for the new repository. */
  SVN_ERR(create_repos_id(&new_repos_id, repos_root_url, repos_uuid,
                          wcroot->sdb, scratch_pool));

  /* Set the (base and working) repos_ids and clear the dav_caches */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_RECURSIVE_UPDATE_NODE_REPO));
  SVN_ERR(svn_sqlite__bindf(stmt, "isii", wcroot->wc_id, local_relpath,
                            old_repos_id, new_repos_id));
  SVN_ERR(svn_sqlite__step_done(stmt));

  if (have_base_node)
    {
      /* Update any locks for the root or its children. */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_UPDATE_LOCK_REPOS_ID));
      SVN_ERR(svn_sqlite__bindf(stmt, "ii", old_repos_id, new_repos_id));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  /* ### TODO: Update urls stored in inherited properties...
               What about urls in conflicts?
                 # We can probably keep these as they are only used
                   for showing full urls to the user */

  return SVN_NO_ERROR;
}