#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_spillbuf_t ;
struct spillbuf_baton {int /*<<< orphan*/  scratch_pool; TYPE_1__* reader; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 struct spillbuf_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_handler_spillbuf ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct spillbuf_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_handler_spillbuf ; 

svn_stream_t *
svn_stream__from_spillbuf(svn_spillbuf_t *buf,
                          apr_pool_t *result_pool)
{
  svn_stream_t *stream;
  struct spillbuf_baton *sb = apr_palloc(result_pool, sizeof(*sb));

  sb->reader = apr_pcalloc(result_pool, sizeof(*sb->reader));
  sb->reader->buf = buf;
  sb->scratch_pool = svn_pool_create(result_pool);

  stream = svn_stream_create(sb, result_pool);

  svn_stream_set_read2(stream, NULL /* only full read support */,
                       read_handler_spillbuf);
  svn_stream_set_write(stream, write_handler_spillbuf);

  return stream;
}