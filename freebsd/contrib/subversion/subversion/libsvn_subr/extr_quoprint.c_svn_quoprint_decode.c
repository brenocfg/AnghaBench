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
struct decode_baton {int /*<<< orphan*/ * pool; scalar_t__ buflen; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct decode_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_data ; 
 int /*<<< orphan*/  finish_decoding_data ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct decode_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_stream_t *
svn_quoprint_decode(svn_stream_t *output, apr_pool_t *pool)
{
  apr_pool_t *subpool = svn_pool_create(pool);
  struct decode_baton *db = apr_palloc(subpool, sizeof(*db));
  svn_stream_t *stream;

  db->output = output;
  db->buflen = 0;
  db->pool = subpool;
  stream = svn_stream_create(db, pool);
  svn_stream_set_write(stream, decode_data);
  svn_stream_set_close(stream, finish_decoding_data);
  return stream;
}