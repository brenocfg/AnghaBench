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
struct TYPE_4__ {int /*<<< orphan*/  timeout_fn; void* timeout_baton; int /*<<< orphan*/ * out_stream; int /*<<< orphan*/ * in_stream; } ;
typedef  TYPE_1__ svn_ra_svn__stream_t ;
typedef  int /*<<< orphan*/  ra_svn_timeout_fn_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_ra_svn__stream_t *
svn_ra_svn__stream_create(svn_stream_t *in_stream,
                          svn_stream_t *out_stream,
                          void *timeout_baton,
                          ra_svn_timeout_fn_t timeout_cb,
                          apr_pool_t *pool)
{
  svn_ra_svn__stream_t *s = apr_palloc(pool, sizeof(*s));
  s->in_stream = in_stream;
  s->out_stream = out_stream;
  s->timeout_baton = timeout_baton;
  s->timeout_fn = timeout_cb;
  return s;
}