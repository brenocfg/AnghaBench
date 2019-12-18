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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct encode_baton {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  break_lines; scalar_t__ linelen; scalar_t__ buflen; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct encode_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  encode_data ; 
 int /*<<< orphan*/  finish_encoding_data ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct encode_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_stream_t *
svn_base64_encode2(svn_stream_t *output,
                   svn_boolean_t break_lines,
                   apr_pool_t *pool)
{
  struct encode_baton *eb = apr_palloc(pool, sizeof(*eb));
  svn_stream_t *stream;

  eb->output = output;
  eb->buflen = 0;
  eb->linelen = 0;
  eb->break_lines = break_lines;
  eb->scratch_pool = svn_pool_create(pool);
  stream = svn_stream_create(eb, pool);
  svn_stream_set_write(stream, encode_data);
  svn_stream_set_close(stream, finish_encoding_data);
  return stream;
}