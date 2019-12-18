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
struct svn_stream_t {int dummy; } ;
typedef  struct svn_stream_t svn_stream_t ;
struct zbaton {int /*<<< orphan*/  read_flush; int /*<<< orphan*/ * read_buffer; int /*<<< orphan*/ * pool; struct svn_stream_t* substream; int /*<<< orphan*/ * out; int /*<<< orphan*/  in; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 struct zbaton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_handler_gz ; 
 int /*<<< orphan*/  read_handler_gz ; 
 struct svn_stream_t* svn_stream_create (struct zbaton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (struct svn_stream_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (struct svn_stream_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (struct svn_stream_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_handler_gz ; 

svn_stream_t *
svn_stream_compressed(svn_stream_t *stream, apr_pool_t *pool)
{
  struct svn_stream_t *zstream;
  struct zbaton *baton;

  assert(stream != NULL);

  baton = apr_palloc(pool, sizeof(*baton));
  baton->in = baton->out = NULL;
  baton->substream = stream;
  baton->pool = pool;
  baton->read_buffer = NULL;
  baton->read_flush = Z_SYNC_FLUSH;

  zstream = svn_stream_create(baton, pool);
  svn_stream_set_read2(zstream, NULL /* only full read support */,
                       read_handler_gz);
  svn_stream_set_write(zstream, write_handler_gz);
  svn_stream_set_close(zstream, close_handler_gz);

  return zstream;
}