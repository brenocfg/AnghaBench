#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ window_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_18__ {int len; char* data; } ;
struct TYPE_20__ {int end_offset; int /*<<< orphan*/  ver; TYPE_3__ window; } ;
typedef  TYPE_5__ svn_fs_fs__raw_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_21__ {int current; int size; int /*<<< orphan*/  chunk_index; int /*<<< orphan*/  raw_window_cache; int /*<<< orphan*/  ver; TYPE_2__* sfile; int /*<<< orphan*/  start; int /*<<< orphan*/  window_cache; } ;
typedef  TYPE_6__ rep_state_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;
struct TYPE_17__ {TYPE_1__* rfile; } ;
struct TYPE_16__ {int /*<<< orphan*/  file; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  auto_read_diff_version (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_raw_window_end ; 
 int /*<<< orphan*/  get_txdelta_window_end ; 
 TYPE_4__* get_window_key (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  rs_aligned_seek (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta__read_raw_window_len (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
cache_windows(svn_fs_t *fs,
              rep_state_t *rs,
              apr_off_t max_offset,
              apr_pool_t *pool)
{
  apr_pool_t *iterpool = svn_pool_create(pool);

  SVN_ERR(auto_read_diff_version(rs, iterpool));

  while (rs->current < rs->size)
    {
      apr_off_t end_offset;
      svn_boolean_t found = FALSE;
      window_cache_key_t key = { 0 };

      svn_pool_clear(iterpool);

      if (max_offset != -1 && rs->start + rs->current >= max_offset)
        {
          svn_pool_destroy(iterpool);
          return SVN_NO_ERROR;
        }

      /* We don't need to read the data again if it is already in cache.
       * It might be cached as either raw or parsed window.
       */
      SVN_ERR(svn_cache__get_partial((void **) &end_offset, &found,
                                     rs->raw_window_cache,
                                     get_window_key(&key, rs),
                                     get_raw_window_end, NULL,
                                     iterpool));
      if (! found)
        SVN_ERR(svn_cache__get_partial((void **) &end_offset, &found,
                                       rs->window_cache, &key,
                                       get_txdelta_window_end, NULL,
                                       iterpool));

      if (found)
        {
          rs->current = end_offset;
        }
      else
        {
          /* Read, decode and cache the window. */
          svn_fs_fs__raw_cached_window_t window;
          apr_off_t start_offset = rs->start + rs->current;
          apr_size_t window_len;
          char *buf;

          /* navigate to the current window */
          SVN_ERR(rs_aligned_seek(rs, NULL, start_offset, iterpool));
          SVN_ERR(svn_txdelta__read_raw_window_len(&window_len,
                                                   rs->sfile->rfile->stream,
                                                   iterpool));

          /* Read the raw window. */
          buf = apr_palloc(iterpool, window_len + 1);
          SVN_ERR(rs_aligned_seek(rs, NULL, start_offset, iterpool));
          SVN_ERR(svn_io_file_read_full2(rs->sfile->rfile->file, buf,
                                         window_len, NULL, NULL, iterpool));
          buf[window_len] = 0;

          /* update relative offset in representation */
          rs->current += window_len;

          /* Construct the cachable raw window object. */
          window.end_offset = rs->current;
          window.window.len = window_len;
          window.window.data = buf;
          window.ver = rs->ver;

          /* cache the window now */
          SVN_ERR(svn_cache__set(rs->raw_window_cache, &key, &window,
                                 iterpool));
        }

      if (rs->current > rs->size)
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Reading one svndiff window read beyond "
                                            "the end of the representation"));

      rs->chunk_index++;
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}