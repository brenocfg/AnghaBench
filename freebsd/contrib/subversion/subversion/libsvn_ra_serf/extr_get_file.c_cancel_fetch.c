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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {scalar_t__ read_size; scalar_t__ aborted_read_size; scalar_t__ aborted_read; scalar_t__ read_headers; } ;
typedef  TYPE_1__ stream_ctx_t ;
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static svn_error_t *
cancel_fetch(serf_request_t *request,
             serf_bucket_t *response,
             int status_code,
             void *baton)
{
  stream_ctx_t *fetch_ctx = baton;

  /* Uh-oh.  Our connection died on us.
   *
   * The core ra_serf layer will requeue our request - we just need to note
   * that we got cut off in the middle of our song.
   */
  if (!response)
    {
      /* If we already started the fetch and opened the file handle, we need
       * to hold subsequent read() ops until we get back to where we were
       * before the close and we can then resume the textdelta() calls.
       */
      if (fetch_ctx->read_headers)
        {
          if (!fetch_ctx->aborted_read && fetch_ctx->read_size)
            {
              fetch_ctx->aborted_read = TRUE;
              fetch_ctx->aborted_read_size = fetch_ctx->read_size;
            }
          fetch_ctx->read_size = 0;
        }

      return SVN_NO_ERROR;
    }

  /* We have no idea what went wrong. */
  SVN_ERR_MALFUNCTION();
}