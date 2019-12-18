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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_stream_lazyopen_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  open_on_close; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * real_stream; void* open_baton; int /*<<< orphan*/  open_func; } ;
typedef  TYPE_1__ lazyopen_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_handler_lazyopen ; 
 int /*<<< orphan*/  data_available_handler_lazyopen ; 
 int /*<<< orphan*/  mark_handler_lazyopen ; 
 int /*<<< orphan*/  read_full_handler_lazyopen ; 
 int /*<<< orphan*/  read_handler_lazyopen ; 
 int /*<<< orphan*/  readline_handler_lazyopen ; 
 int /*<<< orphan*/  seek_handler_lazyopen ; 
 int /*<<< orphan*/  skip_handler_lazyopen ; 
 int /*<<< orphan*/ * svn_stream_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_data_available (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_readline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_handler_lazyopen ; 

svn_stream_t *
svn_stream_lazyopen_create(svn_stream_lazyopen_func_t open_func,
                           void *open_baton,
                           svn_boolean_t open_on_close,
                           apr_pool_t *result_pool)
{
  lazyopen_baton_t *lob = apr_pcalloc(result_pool, sizeof(*lob));
  svn_stream_t *stream;

  lob->open_func = open_func;
  lob->open_baton = open_baton;
  lob->real_stream = NULL;
  lob->pool = result_pool;
  lob->open_on_close = open_on_close;

  stream = svn_stream_create(lob, result_pool);
  svn_stream_set_read2(stream, read_handler_lazyopen,
                       read_full_handler_lazyopen);
  svn_stream_set_skip(stream, skip_handler_lazyopen);
  svn_stream_set_write(stream, write_handler_lazyopen);
  svn_stream_set_close(stream, close_handler_lazyopen);
  svn_stream_set_mark(stream, mark_handler_lazyopen);
  svn_stream_set_seek(stream, seek_handler_lazyopen);
  svn_stream_set_data_available(stream, data_available_handler_lazyopen);
  svn_stream_set_readline(stream, readline_handler_lazyopen);

  return stream;
}