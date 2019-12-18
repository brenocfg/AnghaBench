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
struct TYPE_4__ {void* baton; } ;
typedef  TYPE_1__ svn_stream_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_stream_t *
svn_stream_create(void *baton, apr_pool_t *pool)
{
  svn_stream_t *stream;

  stream = apr_pcalloc(pool, sizeof(*stream));
  stream->baton = baton;
  return stream;
}