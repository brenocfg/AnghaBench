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
struct TYPE_3__ {scalar_t__ scratch_pool; int /*<<< orphan*/  result_pool; int /*<<< orphan*/  all_data; scalar_t__ collect_bucket; scalar_t__ file; } ;
typedef  TYPE_1__ svn_ra_serf__request_body_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  allocate_all (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_file_buffer_set (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_flush (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_pool_destroy (scalar_t__) ; 

__attribute__((used)) static svn_error_t *
request_body_stream_close(void *baton)
{
  svn_ra_serf__request_body_t *b = baton;

  if (b->file)
    {
      /* We need to flush the file, make it unbuffered (so that it can be
       * zero-copied via mmap), and reset the position before attempting
       * to deliver the file.
       *
       * N.B. If we have APR 1.3+, we can unbuffer the file to let us use
       * mmap and zero-copy the PUT body.  However, on older APR versions,
       * we can't check the buffer status; but serf will fall through and
       * create a file bucket for us on the buffered handle.
       */

      SVN_ERR(svn_io_file_flush(b->file, b->scratch_pool));
      apr_file_buffer_set(b->file, NULL, 0);
    }
  else if (b->collect_bucket)
    b->all_data = allocate_all(b, b->result_pool);

  if (b->scratch_pool)
    svn_pool_destroy(b->scratch_pool);

  return SVN_NO_ERROR;
}