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
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FOPEN_READ ; 
 int /*<<< orphan*/  APR_FPROT_OS_DEFAULT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_logmsg_from_patch(const char **logmsg,
                       const char *patch_abspath,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  apr_file_t *file;
  svn_stream_t *stream;
  svn_boolean_t eof;
  svn_stringbuf_t *line;

  SVN_ERR(svn_io_file_open(&file, patch_abspath,
                           APR_FOPEN_READ, APR_FPROT_OS_DEFAULT, scratch_pool));
  stream = svn_stream_from_aprfile2(file, FALSE /*disown*/, scratch_pool);
  SVN_ERR(svn_stream_readline(stream, &line, "\n", &eof, result_pool));
  SVN_ERR(svn_stream_close(stream));
  *logmsg = line->data;
  return SVN_NO_ERROR;
}