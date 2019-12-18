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
 int /*<<< orphan*/  mark_handler_empty ; 
 int /*<<< orphan*/  read_handler_empty ; 
 int /*<<< orphan*/  seek_handler_empty ; 
 int /*<<< orphan*/ * svn_stream_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_handler_empty ; 

svn_stream_t *
svn_stream_empty(apr_pool_t *pool)
{
  svn_stream_t *stream;

  stream = svn_stream_create(NULL, pool);
  svn_stream_set_read2(stream, read_handler_empty, read_handler_empty);
  svn_stream_set_write(stream, write_handler_empty);
  svn_stream_set_mark(stream, mark_handler_empty);
  svn_stream_set_seek(stream, seek_handler_empty);
  return stream;
}