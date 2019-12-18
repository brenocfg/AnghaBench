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
typedef  int /*<<< orphan*/  svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_window_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

svn_error_t *
svn_txdelta__read_raw_window_len(apr_size_t *window_len,
                                 svn_stream_t *stream,
                                 apr_pool_t *pool)
{
  svn_filesize_t sview_offset;
  apr_size_t sview_len, tview_len, inslen, newlen, header_len;

  SVN_ERR(read_window_header(stream, &sview_offset, &sview_len, &tview_len,
                             &inslen, &newlen, &header_len));

  *window_len = inslen + newlen + header_len;
  return SVN_NO_ERROR;
}