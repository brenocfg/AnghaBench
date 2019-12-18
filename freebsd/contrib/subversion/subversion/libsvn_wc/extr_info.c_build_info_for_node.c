#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * conflicts; int /*<<< orphan*/  wcroot_abspath; void* depth; void* schedule; int /*<<< orphan*/  moved_to_abspath; int /*<<< orphan*/  checksum; int /*<<< orphan*/ * moved_from_abspath; void* copyfrom_rev; void* copyfrom_url; int /*<<< orphan*/  changelist; int /*<<< orphan*/  recorded_time; int /*<<< orphan*/  recorded_size; } ;
typedef  TYPE_2__ svn_wc_info_t ;
struct TYPE_16__ {char const* repos_root_URL; char const* repos_UUID; TYPE_1__* lock; TYPE_2__* wc_info; int /*<<< orphan*/  size; void* URL; void* rev; int /*<<< orphan*/  kind; int /*<<< orphan*/  last_changed_author; int /*<<< orphan*/  last_changed_date; int /*<<< orphan*/  last_changed_rev; } ;
typedef  TYPE_3__ svn_wc__info2_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
struct TYPE_17__ {int /*<<< orphan*/  date; int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;
typedef  TYPE_4__ svn_wc__db_lock_t ;
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_18__ {scalar_t__ apr_err; } ;
typedef  TYPE_5__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {int /*<<< orphan*/  creation_date; int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/  SVN_INVALID_FILESIZE ; 
 void* SVN_INVALID_REVNUM ; 
 TYPE_5__* SVN_NO_ERROR ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* svn_depth_exclude ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_5__*) ; 
 TYPE_5__* svn_error_trace (TYPE_5__*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 void* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_get_wcroot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_info_below_working (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,int /*<<< orphan*/ *,void**,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,void**,TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_pristine_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_repos_info (void**,char const**,char const**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_scan_deletion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_wc__db_scan_moved (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 
 int /*<<< orphan*/  svn_wc__read_conflicts (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_wc_schedule_add ; 
 void* svn_wc_schedule_delete ; 
 void* svn_wc_schedule_normal ; 
 void* svn_wc_schedule_replace ; 

__attribute__((used)) static svn_error_t *
build_info_for_node(svn_wc__info2_t **info,
                     svn_wc__db_t *db,
                     const char *local_abspath,
                     svn_node_kind_t kind,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  svn_wc__info2_t *tmpinfo;
  const char *repos_relpath;
  svn_wc__db_status_t status;
  svn_node_kind_t db_kind;
  const char *original_repos_relpath;
  const char *original_repos_root_url;
  const char *original_uuid;
  svn_revnum_t original_revision;
  svn_wc__db_lock_t *lock;
  svn_boolean_t conflicted;
  svn_boolean_t op_root;
  svn_boolean_t have_base;
  svn_boolean_t have_more_work;
  svn_wc_info_t *wc_info;

  tmpinfo = apr_pcalloc(result_pool, sizeof(*tmpinfo));
  tmpinfo->kind = kind;

  wc_info = apr_pcalloc(result_pool, sizeof(*wc_info));
  tmpinfo->wc_info = wc_info;

  wc_info->copyfrom_rev = SVN_INVALID_REVNUM;

  SVN_ERR(svn_wc__db_read_info(&status, &db_kind, &tmpinfo->rev,
                               &repos_relpath,
                               &tmpinfo->repos_root_URL, &tmpinfo->repos_UUID,
                               &tmpinfo->last_changed_rev,
                               &tmpinfo->last_changed_date,
                               &tmpinfo->last_changed_author,
                               &wc_info->depth, &wc_info->checksum, NULL,
                               &original_repos_relpath,
                               &original_repos_root_url, &original_uuid,
                               &original_revision, &lock,
                               &wc_info->recorded_size,
                               &wc_info->recorded_time,
                               &wc_info->changelist,
                               &conflicted, &op_root, NULL, NULL,
                               &have_base, &have_more_work, NULL,
                               db, local_abspath,
                               result_pool, scratch_pool));

  if (original_repos_root_url != NULL)
    {
      tmpinfo->repos_root_URL = original_repos_root_url;
      tmpinfo->repos_UUID = original_uuid;
    }

  if (status == svn_wc__db_status_added)
    {
      /* ### We should also just be fetching the true BASE revision
         ### here, which means copied items would also not have a
         ### revision to display.  But WC-1 wants to show the revision of
         ### copy targets as the copyfrom-rev.  *sigh* */

      if (original_repos_relpath)
        {
          /* Root or child of copy */
          tmpinfo->rev = original_revision;

          if (op_root)
            {
              svn_error_t *err;
              wc_info->copyfrom_url =
                    svn_path_url_add_component2(tmpinfo->repos_root_URL,
                                                original_repos_relpath,
                                                result_pool);

              wc_info->copyfrom_rev = original_revision;

              err = svn_wc__db_scan_moved(&wc_info->moved_from_abspath,
                                          NULL, NULL, NULL,
                                          db, local_abspath,
                                          result_pool, scratch_pool);

              if (err)
                {
                   if (err->apr_err != SVN_ERR_WC_PATH_UNEXPECTED_STATUS)
                      return svn_error_trace(err);
                   svn_error_clear(err);
                   wc_info->moved_from_abspath = NULL;
                }
            }
        }

      /* ### We should be able to avoid both these calls with the information
         from read_info() in most cases */
      if (! op_root)
        wc_info->schedule = svn_wc_schedule_normal;
      else if (! have_more_work && ! have_base)
        wc_info->schedule = svn_wc_schedule_add;
      else
        {
          svn_wc__db_status_t below_working;
          svn_boolean_t have_work;

          SVN_ERR(svn_wc__db_info_below_working(&have_base, &have_work,
                                                &below_working,
                                                db, local_abspath,
                                                scratch_pool));

          /* If the node is not present or deleted (read: not present
             in working), then the node is not a replacement */
          if (below_working != svn_wc__db_status_not_present
              && below_working != svn_wc__db_status_deleted)
            {
              wc_info->schedule = svn_wc_schedule_replace;
            }
          else
            wc_info->schedule = svn_wc_schedule_add;
        }
      SVN_ERR(svn_wc__db_read_repos_info(NULL, &repos_relpath,
                                         &tmpinfo->repos_root_URL,
                                         &tmpinfo->repos_UUID,
                                         db, local_abspath,
                                         result_pool, scratch_pool));

      tmpinfo->URL = svn_path_url_add_component2(tmpinfo->repos_root_URL,
                                                 repos_relpath, result_pool);
    }
  else if (status == svn_wc__db_status_deleted)
    {
      svn_wc__db_status_t w_status;

      SVN_ERR(svn_wc__db_read_pristine_info(&w_status, &tmpinfo->kind,
                                            &tmpinfo->last_changed_rev,
                                            &tmpinfo->last_changed_date,
                                            &tmpinfo->last_changed_author,
                                            &wc_info->depth,
                                            &wc_info->checksum,
                                            NULL, NULL, NULL,
                                            db, local_abspath,
                                            result_pool, scratch_pool));

      if (w_status == svn_wc__db_status_deleted)
        {
          /* We have a working not-present status. We don't know anything
             about this node, but it *is visible* in STATUS.

             Let's tell that it is excluded */

          wc_info->depth = svn_depth_exclude;
          tmpinfo->kind = svn_node_unknown;
        }

      /* And now fetch the url and revision of what will be deleted */
      SVN_ERR(svn_wc__db_scan_deletion(NULL, &wc_info->moved_to_abspath,
                                       NULL, NULL,
                                       db, local_abspath,
                                       scratch_pool, scratch_pool));

      SVN_ERR(svn_wc__db_read_repos_info(&tmpinfo->rev, &repos_relpath,
                                         &tmpinfo->repos_root_URL,
                                         &tmpinfo->repos_UUID,
                                         db, local_abspath,
                                         result_pool, scratch_pool));

      wc_info->schedule = svn_wc_schedule_delete;
      tmpinfo->URL = svn_path_url_add_component2(tmpinfo->repos_root_URL,
                                                 repos_relpath, result_pool);
    }
  else if (status == svn_wc__db_status_not_present
           || status == svn_wc__db_status_server_excluded)
    {
      *info = NULL;
      return SVN_NO_ERROR;
    }
  else if (status == svn_wc__db_status_excluded && !repos_relpath)
    {
      /* We have a WORKING exclude. Avoid segfault on no repos info */

      SVN_ERR(svn_wc__db_read_repos_info(NULL, &repos_relpath,
                                         &tmpinfo->repos_root_URL,
                                         &tmpinfo->repos_UUID,
                                         db, local_abspath,
                                         result_pool, scratch_pool));

      wc_info->schedule = svn_wc_schedule_normal;
      tmpinfo->URL = svn_path_url_add_component2(tmpinfo->repos_root_URL,
                                                 repos_relpath, result_pool);
      tmpinfo->wc_info->depth = svn_depth_exclude;
    }
  else
    {
      /* Just a BASE node. We have all the info we need */
      tmpinfo->URL = svn_path_url_add_component2(tmpinfo->repos_root_URL,
                                                 repos_relpath,
                                                 result_pool);
      wc_info->schedule = svn_wc_schedule_normal;

      if (status == svn_wc__db_status_excluded)
        wc_info->depth = svn_depth_exclude;
    }

  /* A default */
  tmpinfo->size = SVN_INVALID_FILESIZE;

  SVN_ERR(svn_wc__db_get_wcroot(&tmpinfo->wc_info->wcroot_abspath, db,
                                local_abspath, result_pool, scratch_pool));

  if (conflicted)
    SVN_ERR(svn_wc__read_conflicts(&wc_info->conflicts, NULL,
                                   db, local_abspath,
                                   FALSE /* create tempfiles */,
                                   FALSE /* only tree conflicts */,
                                   result_pool, scratch_pool));
  else
    wc_info->conflicts = NULL;

  /* lock stuff */
  if (lock != NULL)
    {
      tmpinfo->lock = apr_pcalloc(result_pool, sizeof(*(tmpinfo->lock)));
      tmpinfo->lock->token         = lock->token;
      tmpinfo->lock->owner         = lock->owner;
      tmpinfo->lock->comment       = lock->comment;
      tmpinfo->lock->creation_date = lock->date;
    }

  *info = tmpinfo;
  return SVN_NO_ERROR;
}