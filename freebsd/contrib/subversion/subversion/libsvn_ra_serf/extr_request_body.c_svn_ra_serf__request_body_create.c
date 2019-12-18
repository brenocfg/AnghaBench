#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  stream; int /*<<< orphan*/ * result_pool; int /*<<< orphan*/  in_memory_size; } ;
typedef  TYPE_1__ svn_ra_serf__request_body_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  request_body_stream_close ; 
 int /*<<< orphan*/  request_body_stream_write ; 
 int /*<<< orphan*/  svn_stream_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_ra_serf__request_body_t *
svn_ra_serf__request_body_create(apr_size_t in_memory_size,
                                 apr_pool_t *result_pool)
{
  svn_ra_serf__request_body_t *body = apr_pcalloc(result_pool, sizeof(*body));

  body->in_memory_size = in_memory_size;
  body->result_pool = result_pool;
  body->stream = svn_stream_create(body, result_pool);

  svn_stream_set_write(body->stream, request_body_stream_write);
  svn_stream_set_close(body->stream, request_body_stream_close);

  return body;
}