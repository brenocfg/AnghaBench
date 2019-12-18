#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct checksum_stream_baton {int /*<<< orphan*/  proxy; int /*<<< orphan*/  pool; scalar_t__ write_ctx; int /*<<< orphan*/  write_checksum; scalar_t__ read_ctx; int /*<<< orphan*/  read_checksum; scalar_t__ read_more; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN__STREAM_CHUNK_SIZE ; 
 char* apr_palloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_full_handler_checksum (void*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_final (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_handler_checksum(void *baton)
{
  struct checksum_stream_baton *btn = baton;

  /* If we're supposed to drain the stream, do so before finalizing the
     checksum. */
  if (btn->read_more)
    {
      char *buf = apr_palloc(btn->pool, SVN__STREAM_CHUNK_SIZE);
      apr_size_t len = SVN__STREAM_CHUNK_SIZE;

      do
        {
          SVN_ERR(read_full_handler_checksum(baton, buf, &len));
        }
      while (btn->read_more);
    }

  if (btn->read_ctx)
    SVN_ERR(svn_checksum_final(btn->read_checksum, btn->read_ctx, btn->pool));

  if (btn->write_ctx)
    SVN_ERR(svn_checksum_final(btn->write_checksum, btn->write_ctx, btn->pool));

  return svn_error_trace(svn_stream_close(btn->proxy));
}