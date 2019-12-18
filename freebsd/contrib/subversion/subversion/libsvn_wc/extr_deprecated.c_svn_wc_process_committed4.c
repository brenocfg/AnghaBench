#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_committed_queue_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_WC_DB_ERROR ; 
 int /*<<< orphan*/ * svn_checksum__from_digest_md5 (unsigned char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_pristine_get_sha1 (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_committed_queue_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_process_committed_queue2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_queue_committed3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_process_committed4(const char *path,
                          svn_wc_adm_access_t *adm_access,
                          svn_boolean_t recurse,
                          svn_revnum_t new_revnum,
                          const char *rev_date,
                          const char *rev_author,
                          const apr_array_header_t *wcprop_changes,
                          svn_boolean_t remove_lock,
                          svn_boolean_t remove_changelist,
                          const unsigned char *digest,
                          apr_pool_t *pool)
{
  svn_wc__db_t *db = svn_wc__adm_get_db(adm_access);
  const char *local_abspath;
  const svn_checksum_t *md5_checksum;
  const svn_checksum_t *sha1_checksum = NULL;
  svn_wc_context_t *wc_ctx;
  svn_wc_committed_queue_t *queue;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));
  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL, db, pool));

  if (digest)
    md5_checksum = svn_checksum__from_digest_md5(digest, pool);
  else
    md5_checksum = NULL;

  if (md5_checksum != NULL)
    {
      svn_error_t *err;
      err = svn_wc__db_pristine_get_sha1(&sha1_checksum, db,
                                         local_abspath, md5_checksum,
                                         pool, pool);

      if (err && err->apr_err == SVN_ERR_WC_DB_ERROR)
        {
          svn_error_clear(err);
          sha1_checksum = NULL;
        }
      else
        SVN_ERR(err);
    }

  queue = svn_wc_committed_queue_create(pool);
  SVN_ERR(svn_wc_queue_committed3(queue, wc_ctx, local_abspath, recurse,
                                  wcprop_changes, remove_lock,
                                  remove_changelist,
                                  sha1_checksum /* or NULL if not modified
                                                           or directory */,
                                  pool));

  SVN_ERR(svn_wc_process_committed_queue2(queue, wc_ctx,
                                          new_revnum, rev_date, rev_author,
                                          NULL, NULL /* cancel */,
                                          pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}