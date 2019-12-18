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
struct TYPE_4__ {int /*<<< orphan*/  md5_digest; int /*<<< orphan*/  next_window; void* baton; } ;
typedef  TYPE_1__ svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_txdelta_next_window_fn_t ;
typedef  int /*<<< orphan*/  svn_txdelta_md5_digest_fn_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_txdelta_stream_t *
svn_txdelta_stream_create(void *baton,
                          svn_txdelta_next_window_fn_t next_window,
                          svn_txdelta_md5_digest_fn_t md5_digest,
                          apr_pool_t *pool)
{
  svn_txdelta_stream_t *stream = apr_palloc(pool, sizeof(*stream));

  stream->baton = baton;
  stream->next_window = next_window;
  stream->md5_digest = md5_digest;

  return stream;
}