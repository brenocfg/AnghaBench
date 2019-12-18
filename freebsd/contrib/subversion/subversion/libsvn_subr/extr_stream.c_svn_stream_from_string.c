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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct string_stream_baton {scalar_t__ amt_read; int /*<<< orphan*/  const* str; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct string_stream_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  data_available_handler_string ; 
 int /*<<< orphan*/  mark_handler_string ; 
 int /*<<< orphan*/  read_handler_string ; 
 int /*<<< orphan*/  readline_handler_string ; 
 int /*<<< orphan*/  seek_handler_string ; 
 int /*<<< orphan*/  skip_handler_string ; 
 int /*<<< orphan*/ * svn_stream_create (struct string_stream_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_data_available (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_readline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_stream_t *
svn_stream_from_string(const svn_string_t *str,
                       apr_pool_t *pool)
{
  svn_stream_t *stream;
  struct string_stream_baton *baton;

  if (! str)
    return svn_stream_empty(pool);

  baton = apr_palloc(pool, sizeof(*baton));
  baton->str = str;
  baton->amt_read = 0;
  stream = svn_stream_create(baton, pool);
  svn_stream_set_read2(stream, read_handler_string, read_handler_string);
  svn_stream_set_mark(stream, mark_handler_string);
  svn_stream_set_seek(stream, seek_handler_string);
  svn_stream_set_skip(stream, skip_handler_string);
  svn_stream_set_data_available(stream, data_available_handler_string);
  svn_stream_set_readline(stream, readline_handler_string);
  return stream;
}