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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_from_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_string_from_stream2(svn_string_t **result,
                        svn_stream_t *stream,
                        apr_size_t len_hint,
                        apr_pool_t *result_pool)
{
  svn_stringbuf_t *buf;

  SVN_ERR(svn_stringbuf_from_stream(&buf, stream, len_hint, result_pool));
  *result = svn_stringbuf__morph_into_string(buf);

  SVN_ERR(svn_stream_close(stream));

  return SVN_NO_ERROR;
}