#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
struct TYPE_7__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_2__ svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_MD5_DIGESTSIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/ * svn_io_open_unique_file3 (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream__from_aprfile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__context_create_with_db (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__internal_transmit_text_deltas (int /*<<< orphan*/ ,TYPE_2__ const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (TYPE_1__*) ; 

svn_error_t *
svn_wc_transmit_text_deltas2(const char **tempfile,
                             unsigned char digest[],
                             const char *path,
                             svn_wc_adm_access_t *adm_access,
                             svn_boolean_t fulltext,
                             const svn_delta_editor_t *editor,
                             void *file_baton,
                             apr_pool_t *pool)
{
  const char *local_abspath;
  svn_wc_context_t *wc_ctx;
  const svn_checksum_t *new_text_base_md5_checksum;
  svn_stream_t *tempstream;
  svn_error_t *err;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));
  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL /* config */,
                                         svn_wc__adm_get_db(adm_access),
                                         pool));
  if (tempfile)
    {
      apr_file_t *f;

      /* The temporary file can't be the same location as in 1.6 because the
       * admin directory no longer exists. */
      SVN_ERR(svn_io_open_unique_file3(&f, tempfile, NULL,
                                       svn_io_file_del_none,
                                       pool, pool));
      tempstream = svn_stream__from_aprfile(f, FALSE, TRUE, pool);
    }
  else
    {
      tempstream = NULL;
    }

  err = svn_wc__internal_transmit_text_deltas(svn_stream_disown(tempstream, pool),
                                              (digest
                                               ? &new_text_base_md5_checksum
                                               : NULL),
                                              NULL, wc_ctx->db,
                                              local_abspath, fulltext,
                                              editor, file_baton,
                                              pool, pool);
  if (tempfile)
    {
      err = svn_error_compose_create(err, svn_stream_close(tempstream));

      if (err)
        {
          err = svn_error_compose_create(
                  err, svn_io_remove_file2(*tempfile, TRUE, pool));
        }
    }

  SVN_ERR(err);

  if (digest)
    memcpy(digest, new_text_base_md5_checksum->digest, APR_MD5_DIGESTSIZE);

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}