#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_committed_queue_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_WC_DB_ERROR ; 
 TYPE_2__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__context_create_with_db (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_pristine_get_sha1 (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_committed_queue_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (TYPE_1__*) ; 
 TYPE_2__* svn_wc_queue_committed3 (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_queue_committed2(svn_wc_committed_queue_t *queue,
                        const char *path,
                        svn_wc_adm_access_t *adm_access,
                        svn_boolean_t recurse,
                        const apr_array_header_t *wcprop_changes,
                        svn_boolean_t remove_lock,
                        svn_boolean_t remove_changelist,
                        const svn_checksum_t *md5_checksum,
                        apr_pool_t *scratch_pool)
{
  svn_wc_context_t *wc_ctx;
  const char *local_abspath;
  const svn_checksum_t *sha1_checksum = NULL;

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL,
                                         svn_wc__adm_get_db(adm_access),
                                         scratch_pool));
  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));

  if (md5_checksum != NULL)
    {
      svn_error_t *err;
      err = svn_wc__db_pristine_get_sha1(&sha1_checksum, wc_ctx->db,
                                         local_abspath, md5_checksum,
                                         svn_wc__get_committed_queue_pool(queue),
                                         scratch_pool);

      /* Don't fail on SHA1 not found */
      if (err && err->apr_err == SVN_ERR_WC_DB_ERROR)
        {
          svn_error_clear(err);
          sha1_checksum = NULL;
        }
      else
        SVN_ERR(err);
    }

  SVN_ERR(svn_wc_queue_committed3(queue, wc_ctx, local_abspath, recurse,
                                  wcprop_changes,
                                  remove_lock, remove_changelist,
                                  sha1_checksum, scratch_pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}