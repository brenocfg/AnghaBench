#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_4__ {int /*<<< orphan*/  baton; int /*<<< orphan*/  (* readline_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stream_readline_bytewise (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_stream_readline(svn_stream_t *stream,
                    svn_stringbuf_t **stringbuf,
                    const char *eol,
                    svn_boolean_t *eof,
                    apr_pool_t *pool)
{
  if (stream->readline_fn)
    {
      /* Use the specific implementation when it's available. */
      SVN_ERR(stream->readline_fn(stream->baton, stringbuf, eol, eof, pool));
    }
  else
    {
      /* Use the default implementation. */
      SVN_ERR(stream_readline_bytewise(stringbuf, eof, eol, stream, pool));
    }

  return SVN_NO_ERROR;
}