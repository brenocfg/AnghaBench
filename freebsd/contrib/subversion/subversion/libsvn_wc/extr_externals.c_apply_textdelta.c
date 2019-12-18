#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_checksum_t ;
struct edit_baton {int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  pool; int /*<<< orphan*/  wri_abspath; int /*<<< orphan*/  db; int /*<<< orphan*/  new_md5_checksum; int /*<<< orphan*/  new_sha1_checksum; int /*<<< orphan*/  install_data; TYPE_1__* original_checksum; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_1__*,TYPE_1__ const*) ; 
 scalar_t__ svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_mismatch_err (TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (TYPE_1__**,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_md5 (TYPE_1__ const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_prepare_install (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_textdelta(void *file_baton,
                const char *base_checksum_digest,
                apr_pool_t *pool,
                svn_txdelta_window_handler_t *handler,
                void **handler_baton)
{
  struct edit_baton *eb = file_baton;
  svn_stream_t *src_stream;
  svn_stream_t *dest_stream;

  if (eb->original_checksum)
    {
      if (base_checksum_digest)
        {
          svn_checksum_t *expected_checksum;
          const svn_checksum_t *original_md5;

          SVN_ERR(svn_checksum_parse_hex(&expected_checksum, svn_checksum_md5,
                                         base_checksum_digest, pool));

          if (eb->original_checksum->kind != svn_checksum_md5)
            SVN_ERR(svn_wc__db_pristine_get_md5(&original_md5,
                                                eb->db, eb->wri_abspath,
                                                eb->original_checksum,
                                                pool, pool));
          else
            original_md5 = eb->original_checksum;

          if (!svn_checksum_match(expected_checksum, original_md5))
            return svn_error_trace(svn_checksum_mismatch_err(
                                    expected_checksum,
                                    original_md5,
                                    pool,
                                    _("Base checksum mismatch for '%s'"),
                                    svn_dirent_local_style(eb->local_abspath,
                                                           pool)));
        }

      SVN_ERR(svn_wc__db_pristine_read(&src_stream, NULL, eb->db,
                                       eb->wri_abspath, eb->original_checksum,
                                       pool, pool));
    }
  else
    src_stream = svn_stream_empty(pool);

  SVN_ERR(svn_wc__db_pristine_prepare_install(&dest_stream,
                                              &eb->install_data,
                                              &eb->new_sha1_checksum,
                                              &eb->new_md5_checksum,
                                              eb->db, eb->wri_abspath,
                                              eb->pool, pool));

  svn_txdelta_apply(src_stream, dest_stream, NULL, eb->local_abspath, pool,
                    handler, handler_baton);

  return SVN_NO_ERROR;
}