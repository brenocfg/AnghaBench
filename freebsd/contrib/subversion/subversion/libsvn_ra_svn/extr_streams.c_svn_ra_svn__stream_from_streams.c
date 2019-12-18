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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__stream_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  file_timeout_cb ; 
 int /*<<< orphan*/ * svn_ra_svn__stream_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream__aprfile (int /*<<< orphan*/ *) ; 

svn_ra_svn__stream_t *
svn_ra_svn__stream_from_streams(svn_stream_t *in_stream,
                                svn_stream_t *out_stream,
                                apr_pool_t *pool)
{
  apr_file_t *file;

  /* If out_stream is backed by an apr_file (e.g. an PIPE) we
     provide a working callback, otherwise the callback ignores
     the timeout.

     The callback is used to make the write non-blocking on
     some error scenarios. ### This (legacy) usage
     breaks the stream promise */
  file = svn_stream__aprfile(out_stream);

  return svn_ra_svn__stream_create(in_stream, out_stream,
                                   file, file_timeout_cb,
                                   pool);
}