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
struct copying_stream_baton {int /*<<< orphan*/ * target; int /*<<< orphan*/ * source; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct copying_stream_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_handler_copy ; 
 int /*<<< orphan*/  read_handler_copy ; 
 int /*<<< orphan*/  seek_handler_copy ; 
 int /*<<< orphan*/ * svn_stream_create (struct copying_stream_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_stream_supports_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_stream_t *
copying_stream(svn_stream_t *source,
               svn_stream_t *target,
               apr_pool_t *pool)
{
  struct copying_stream_baton *baton;
  svn_stream_t *stream;

  baton = apr_palloc(pool, sizeof (*baton));
  baton->source = source;
  baton->target = target;

  stream = svn_stream_create(baton, pool);
  svn_stream_set_read2(stream, NULL /* only full read support */,
                       read_handler_copy);
  svn_stream_set_close(stream, close_handler_copy);

  if (svn_stream_supports_reset(source) && svn_stream_supports_reset(target))
    {
      svn_stream_set_seek(stream, seek_handler_copy);
    }

  return stream;
}