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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_4__ {char const* fs_path; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ presentation_stream_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  data_available_handler_rep ; 
 int /*<<< orphan*/  mark_handler_rep ; 
 int /*<<< orphan*/  read_handler_rep ; 
 int /*<<< orphan*/  readline_handler_rep ; 
 int /*<<< orphan*/  seek_handler_rep ; 
 int /*<<< orphan*/  skip_handler_rep ; 
 int /*<<< orphan*/ * svn_stream_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_data_available (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_readline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_stream_t *
representation_stream(svn_fs_root_t *root,
                      const char *fs_path,
                      apr_pool_t *pool)
{
  svn_stream_t *stream;
  presentation_stream_baton_t *baton;

  baton = apr_pcalloc(pool, sizeof(*baton));
  baton->root = root;
  baton->fs_path = fs_path;
  baton->pool = pool;

  stream = svn_stream_create(baton, pool);
  svn_stream_set_read2(stream, read_handler_rep, read_handler_rep);
  svn_stream_set_mark(stream, mark_handler_rep);
  svn_stream_set_seek(stream, seek_handler_rep);
  svn_stream_set_skip(stream, skip_handler_rep);
  svn_stream_set_data_available(stream, data_available_handler_rep);
  svn_stream_set_readline(stream, readline_handler_rep);
  return stream;
}