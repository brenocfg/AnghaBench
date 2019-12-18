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
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_SVNDIFF_UNEXPECTED_END ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * decode_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_window_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,scalar_t__*) ; 

svn_error_t *
svn_txdelta_read_svndiff_window(svn_txdelta_window_t **window,
                                svn_stream_t *stream,
                                int svndiff_version,
                                apr_pool_t *pool)
{
  svn_filesize_t sview_offset;
  apr_size_t sview_len, tview_len, inslen, newlen, len, header_len;
  unsigned char *buf;

  SVN_ERR(read_window_header(stream, &sview_offset, &sview_len, &tview_len,
                             &inslen, &newlen, &header_len));
  len = inslen + newlen;
  buf = apr_palloc(pool, len);
  SVN_ERR(svn_stream_read_full(stream, (char*)buf, &len));
  if (len < inslen + newlen)
    return svn_error_create(SVN_ERR_SVNDIFF_UNEXPECTED_END, NULL,
                            _("Unexpected end of svndiff input"));
  *window = apr_palloc(pool, sizeof(**window));
  return decode_window(*window, sview_offset, sview_len, tview_len, inslen,
                       newlen, buf, pool, svndiff_version);
}