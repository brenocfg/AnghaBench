#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {TYPE_3__* conn; int /*<<< orphan*/  token; int /*<<< orphan*/  eb; } ;
typedef  TYPE_1__ ra_svn_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  compression_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  check_for_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_svn_svndiff_close_handler ; 
 int /*<<< orphan*/  ra_svn_svndiff_handler ; 
 int /*<<< orphan*/  svn_ra_svn__svndiff_version (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_apply_textdelta (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_stream_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_txdelta_to_svndiff3 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_apply_textdelta(void *file_baton,
                                           const char *base_checksum,
                                           apr_pool_t *pool,
                                           svn_txdelta_window_handler_t *wh,
                                           void **wh_baton)
{
  ra_svn_baton_t *b = file_baton;
  svn_stream_t *diff_stream;

  /* Tell the other side we're starting a text delta. */
  SVN_ERR(check_for_error(b->eb, pool));
  SVN_ERR(svn_ra_svn__write_cmd_apply_textdelta(b->conn, pool, b->token,
                                                base_checksum));

  /* Transform the window stream to an svndiff stream.  Reuse the
   * file baton for the stream handler, since it has all the
   * needed information. */
  diff_stream = svn_stream_create(b, pool);
  svn_stream_set_write(diff_stream, ra_svn_svndiff_handler);
  svn_stream_set_close(diff_stream, ra_svn_svndiff_close_handler);

  svn_txdelta_to_svndiff3(wh, wh_baton, diff_stream,
                          svn_ra_svn__svndiff_version(b->conn),
                          b->conn->compression_level, pool);
  return SVN_NO_ERROR;
}