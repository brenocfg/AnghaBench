#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_fulltext ) (int /*<<< orphan*/ **,void*) ;int /*<<< orphan*/  (* apply_textdelta ) (scalar_t__*,void**,void*) ;} ;
typedef  TYPE_1__ svn_repos_parse_fns3_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_UNEXPECTED_EOF ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * stream_ran_dry () ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,void**,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ **,void*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/ * svn_txdelta_parse_svndiff (scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_text_block(svn_stream_t *stream,
                 svn_filesize_t content_length,
                 svn_boolean_t is_delta,
                 const svn_repos_parse_fns3_t *parse_fns,
                 void *record_baton,
                 char *buffer,
                 apr_size_t buflen,
                 apr_pool_t *pool)
{
  svn_stream_t *text_stream = NULL;
  apr_size_t num_to_read, rlen, wlen;

  if (is_delta)
    {
      svn_txdelta_window_handler_t wh;
      void *whb;

      SVN_ERR(parse_fns->apply_textdelta(&wh, &whb, record_baton));
      if (wh)
        text_stream = svn_txdelta_parse_svndiff(wh, whb, TRUE, pool);
    }
  else
    {
      /* Get a stream to which we can push the data. */
      SVN_ERR(parse_fns->set_fulltext(&text_stream, record_baton));
    }

  /* Regardless of whether or not we have a sink for our data, we
     need to read it. */
  while (content_length)
    {
      if (content_length >= (svn_filesize_t)buflen)
        rlen = buflen;
      else
        rlen = (apr_size_t) content_length;

      num_to_read = rlen;
      SVN_ERR(svn_stream_read_full(stream, buffer, &rlen));
      content_length -= rlen;
      if (rlen != num_to_read)
        return stream_ran_dry();

      if (text_stream)
        {
          /* write however many bytes you read. */
          wlen = rlen;
          SVN_ERR(svn_stream_write(text_stream, buffer, &wlen));
          if (wlen != rlen)
            {
              /* Uh oh, didn't write as many bytes as we read. */
              return svn_error_create(SVN_ERR_STREAM_UNEXPECTED_EOF, NULL,
                                      _("Unexpected EOF writing contents"));
            }
        }
    }

  /* If we opened a stream, we must close it. */
  if (text_stream)
    SVN_ERR(svn_stream_close(text_stream));

  return SVN_NO_ERROR;
}