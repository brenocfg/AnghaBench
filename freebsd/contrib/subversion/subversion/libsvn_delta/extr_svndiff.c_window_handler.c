#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int num_ops; int /*<<< orphan*/  src_ops; } ;
typedef  TYPE_1__ svn_txdelta_window_t ;
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
struct TYPE_12__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct encoder_baton {int /*<<< orphan*/  output; int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  compression_level; int /*<<< orphan*/  version; scalar_t__ header_done; } ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ SVNDIFF_HEADER_SIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  encode_window (TYPE_2__**,TYPE_2__**,TYPE_3__ const**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_svndiff_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_simple_insertion_window (TYPE_1__*,struct encoder_baton*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
window_handler(svn_txdelta_window_t *window, void *baton)
{
  struct encoder_baton *eb = baton;
  apr_size_t len;
  svn_stringbuf_t *instructions;
  svn_stringbuf_t *header;
  const svn_string_t *newdata;

  /* use specialized code if there is no source */
  if (window && !window->src_ops && window->num_ops == 1 && !eb->version)
    return svn_error_trace(send_simple_insertion_window(window, eb));

  /* Make sure we write the header.  */
  if (!eb->header_done)
    {
      len = SVNDIFF_HEADER_SIZE;
      SVN_ERR(svn_stream_write(eb->output, get_svndiff_header(eb->version),
                               &len));
      eb->header_done = TRUE;
    }

  if (window == NULL)
    {
      /* We're done; clean up. */
      SVN_ERR(svn_stream_close(eb->output));

      svn_pool_destroy(eb->scratch_pool);

      return SVN_NO_ERROR;
    }

  svn_pool_clear(eb->scratch_pool);

  SVN_ERR(encode_window(&instructions, &header, &newdata, window,
                        eb->version, eb->compression_level,
                        eb->scratch_pool));

  /* Write out the window.  */
  len = header->len;
  SVN_ERR(svn_stream_write(eb->output, header->data, &len));
  if (instructions->len > 0)
    {
      len = instructions->len;
      SVN_ERR(svn_stream_write(eb->output, instructions->data, &len));
    }
  if (newdata->len > 0)
    {
      len = newdata->len;
      SVN_ERR(svn_stream_write(eb->output, newdata->data, &len));
    }

  return SVN_NO_ERROR;
}