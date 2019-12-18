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
struct baton_tee {int /*<<< orphan*/ * out2; int /*<<< orphan*/ * out1; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct baton_tee* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_handler_tee ; 
 int /*<<< orphan*/ * svn_stream_create (struct baton_tee*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_handler_tee ; 

svn_stream_t *
svn_stream_tee(svn_stream_t *out1,
               svn_stream_t *out2,
               apr_pool_t *pool)
{
  struct baton_tee *baton;
  svn_stream_t *stream;

  if (out1 == NULL)
    return out2;

  if (out2 == NULL)
    return out1;

  baton = apr_palloc(pool, sizeof(*baton));
  baton->out1 = out1;
  baton->out2 = out2;
  stream = svn_stream_create(baton, pool);
  svn_stream_set_write(stream, write_handler_tee);
  svn_stream_set_close(stream, close_handler_tee);

  return stream;
}