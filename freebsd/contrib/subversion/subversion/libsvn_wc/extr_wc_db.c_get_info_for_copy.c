#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * create_repos_id (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scan_addition (scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scan_deletion (char const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char const* svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_fetch_repos_info (char const**,char const**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_excluded ; 

__attribute__((used)) static svn_error_t *
get_info_for_copy(apr_int64_t *copyfrom_id,
                  const char **copyfrom_relpath,
                  svn_revnum_t *copyfrom_rev,
                  svn_wc__db_status_t *status,
                  svn_node_kind_t *kind,
                  svn_boolean_t *op_root,
                  svn_wc__db_wcroot_t *src_wcroot,
                  const char *local_relpath,
                  svn_wc__db_wcroot_t *dst_wcroot,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  const char *repos_relpath;
  svn_revnum_t revision;
  svn_wc__db_status_t node_status;
  apr_int64_t repos_id;
  svn_boolean_t is_op_root;

  SVN_ERR(read_info(&node_status, kind, &revision, &repos_relpath, &repos_id,
                    NULL, NULL, NULL, NULL, NULL, NULL, copyfrom_relpath,
                    copyfrom_id, copyfrom_rev, NULL, NULL, NULL, NULL,
                    NULL, &is_op_root, NULL, NULL,
                    NULL /* have_base */,
                    NULL /* have_more_work */,
                    NULL /* have_work */,
                    src_wcroot, local_relpath, result_pool, scratch_pool));

  if (op_root)
    *op_root = is_op_root;

  if (node_status == svn_wc__db_status_excluded)
    {
      /* The parent cannot be excluded, so look at the parent and then
         adjust the relpath */
      const char *parent_relpath, *base_name;

      svn_dirent_split(&parent_relpath, &base_name, local_relpath,
                       scratch_pool);
      SVN_ERR(get_info_for_copy(copyfrom_id, copyfrom_relpath, copyfrom_rev,
                                NULL, NULL, NULL,
                                src_wcroot, parent_relpath, dst_wcroot,
                                scratch_pool, scratch_pool));
      if (*copyfrom_relpath)
        *copyfrom_relpath = svn_relpath_join(*copyfrom_relpath, base_name,
                                             result_pool);
    }
  else if (node_status == svn_wc__db_status_added)
    {
      SVN_ERR(scan_addition(&node_status, NULL, NULL, NULL, NULL, NULL, NULL,
                            NULL, NULL, NULL, src_wcroot, local_relpath,
                            scratch_pool, scratch_pool));
    }
  else if (node_status == svn_wc__db_status_deleted && is_op_root)
    {
      const char *base_del_relpath, *work_del_relpath;

      SVN_ERR(scan_deletion(&base_del_relpath, NULL,
                            &work_del_relpath,
                            NULL, src_wcroot, local_relpath,
                            scratch_pool, scratch_pool));
      if (work_del_relpath)
        {
          const char *op_root_relpath;
          const char *parent_del_relpath = svn_relpath_dirname(work_del_relpath,
                                                               scratch_pool);

          /* Similar to, but not the same as, the _scan_addition and
             _join above.  Can we use get_copyfrom here? */
          SVN_ERR(scan_addition(NULL, &op_root_relpath,
                                NULL, NULL, /* repos_* */
                                copyfrom_relpath, copyfrom_id, copyfrom_rev,
                                NULL, NULL, NULL,
                                src_wcroot, parent_del_relpath,
                                scratch_pool, scratch_pool));
          *copyfrom_relpath
            = svn_relpath_join(*copyfrom_relpath,
                               svn_relpath_skip_ancestor(op_root_relpath,
                                                         local_relpath),
                               result_pool);
        }
      else if (base_del_relpath)
        {
          SVN_ERR(svn_wc__db_base_get_info_internal(NULL, NULL, copyfrom_rev,
                                                    copyfrom_relpath,
                                                    copyfrom_id, NULL, NULL,
                                                    NULL, NULL, NULL, NULL,
                                                    NULL, NULL, NULL, NULL,
                                                    src_wcroot, local_relpath,
                                                    result_pool,
                                                    scratch_pool));
        }
      else
        SVN_ERR_MALFUNCTION();
    }
  else if (node_status == svn_wc__db_status_deleted)
    {
      /* Keep original_* from read_info() to allow seeing the difference
         between base-deleted and not present */
    }
  else
    {
      *copyfrom_relpath = repos_relpath;
      *copyfrom_rev = revision;
      *copyfrom_id = repos_id;
    }

  if (status)
    *status = node_status;

  if (src_wcroot != dst_wcroot && *copyfrom_relpath)
    {
      const char *repos_root_url;
      const char *repos_uuid;

      /* Pass the right repos-id for the destination db. We can't just use
         the id of the source database, as this value can change after
         relocation (and perhaps also when we start storing multiple
         working copies in a single db)! */

      SVN_ERR(svn_wc__db_fetch_repos_info(&repos_root_url, &repos_uuid,
                                          src_wcroot, *copyfrom_id,
                                          scratch_pool));

      SVN_ERR(create_repos_id(copyfrom_id, repos_root_url, repos_uuid,
                              dst_wcroot->sdb, scratch_pool));
    }

  return SVN_NO_ERROR;
}