#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct file_baton {int /*<<< orphan*/  apply_baton; int /*<<< orphan*/  apply_handler; int /*<<< orphan*/ * pool; int /*<<< orphan*/  path; int /*<<< orphan*/  result_digest; int /*<<< orphan*/  start_md5_checksum; int /*<<< orphan*/ * path_start_revision; TYPE_1__* edit_baton; int /*<<< orphan*/  added; int /*<<< orphan*/ * path_end_revision; scalar_t__ skip; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  text_deltas; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_empty_file (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_file_from_ra (struct file_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lazy_open_result ; 
 int /*<<< orphan*/  lazy_open_source ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_mismatch_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta_noop_window_handler ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_lazyopen_create (int /*<<< orphan*/ ,struct file_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_handler ; 

__attribute__((used)) static svn_error_t *
apply_textdelta(void *file_baton,
                const char *base_md5_digest,
                apr_pool_t *pool,
                svn_txdelta_window_handler_t *handler,
                void **handler_baton)
{
  struct file_baton *fb = file_baton;
  svn_stream_t *src_stream;
  svn_stream_t *result_stream;
  apr_pool_t *scratch_pool = fb->pool;

  /* Skip *everything* within a newly tree-conflicted directory. */
  if (fb->skip)
    {
      *handler = svn_delta_noop_window_handler;
      *handler_baton = NULL;
      return SVN_NO_ERROR;
    }

  /* If we're not sending file text, then ignore any that we receive. */
  if (! fb->edit_baton->text_deltas)
    {
      /* Supply valid paths to indicate there is a text change. */
      SVN_ERR(get_empty_file(fb->edit_baton, &fb->path_start_revision));
      SVN_ERR(get_empty_file(fb->edit_baton, &fb->path_end_revision));

      *handler = svn_delta_noop_window_handler;
      *handler_baton = NULL;

      return SVN_NO_ERROR;
    }

  /* We need the expected pristine file, so go get it */
  if (!fb->added)
    SVN_ERR(get_file_from_ra(fb, FALSE, scratch_pool));
  else
    SVN_ERR(get_empty_file(fb->edit_baton, &(fb->path_start_revision)));

  SVN_ERR_ASSERT(fb->path_start_revision != NULL);

  if (base_md5_digest != NULL)
    {
      svn_checksum_t *base_md5_checksum;

      SVN_ERR(svn_checksum_parse_hex(&base_md5_checksum, svn_checksum_md5,
                                     base_md5_digest, scratch_pool));

      if (!svn_checksum_match(base_md5_checksum, fb->start_md5_checksum))
        return svn_error_trace(svn_checksum_mismatch_err(
                                      base_md5_checksum,
                                      fb->start_md5_checksum,
                                      scratch_pool,
                                      _("Base checksum mismatch for '%s'"),
                                      fb->path));
    }

  /* Open the file to be used as the base for second revision */
  src_stream = svn_stream_lazyopen_create(lazy_open_source, fb, TRUE,
                                          scratch_pool);

  /* Open the file that will become the second revision after applying the
     text delta, it starts empty */
  result_stream = svn_stream_lazyopen_create(lazy_open_result, fb, TRUE,
                                             scratch_pool);

  svn_txdelta_apply(src_stream,
                    result_stream,
                    fb->result_digest,
                    fb->path, fb->pool,
                    &(fb->apply_handler), &(fb->apply_baton));

  *handler = window_handler;
  *handler_baton = file_baton;

  return SVN_NO_ERROR;
}