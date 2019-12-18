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
typedef  int /*<<< orphan*/  svn_spillbuf_reader_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_UNEXPECTED_EOF ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_spillbuf__reader_read (scalar_t__*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_spillbuf__reader_getc(char *c,
                          svn_spillbuf_reader_t *reader,
                          apr_pool_t *scratch_pool)
{
  apr_size_t amt;

  SVN_ERR(svn_spillbuf__reader_read(&amt, reader, c, 1, scratch_pool));
  if (amt == 0)
    return svn_error_create(SVN_ERR_STREAM_UNEXPECTED_EOF, NULL, NULL);

  return SVN_NO_ERROR;
}