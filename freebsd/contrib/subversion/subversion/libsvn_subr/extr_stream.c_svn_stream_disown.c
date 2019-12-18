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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  data_available_disown ; 
 int /*<<< orphan*/  mark_handler_disown ; 
 int /*<<< orphan*/  read_full_handler_disown ; 
 int /*<<< orphan*/  read_handler_disown ; 
 int /*<<< orphan*/  readline_handler_disown ; 
 int /*<<< orphan*/  seek_handler_disown ; 
 int /*<<< orphan*/  skip_handler_disown ; 
 int /*<<< orphan*/ * svn_stream_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_data_available (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_readline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_handler_disown ; 

svn_stream_t *
svn_stream_disown(svn_stream_t *stream, apr_pool_t *pool)
{
  svn_stream_t *s = svn_stream_create(stream, pool);

  svn_stream_set_read2(s, read_handler_disown, read_full_handler_disown);
  svn_stream_set_skip(s, skip_handler_disown);
  svn_stream_set_write(s, write_handler_disown);
  svn_stream_set_mark(s, mark_handler_disown);
  svn_stream_set_seek(s, seek_handler_disown);
  svn_stream_set_data_available(s, data_available_disown);
  svn_stream_set_readline(s, readline_handler_disown);

  return s;
}