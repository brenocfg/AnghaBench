#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* dirpath; void* spill_all_contents; void* delete_on_close; void* maxsize; void* blocksize; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_spillbuf_t ;
typedef  void* svn_boolean_t ;
typedef  void* apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */

__attribute__((used)) static void
init_spillbuf_extended(svn_spillbuf_t *buf,
                       apr_size_t blocksize,
                       apr_size_t maxsize,
                       svn_boolean_t delete_on_close,
                       svn_boolean_t spill_all_contents,
                       const char *dirpath,
                       apr_pool_t *result_pool)
{
  buf->pool = result_pool;
  buf->blocksize = blocksize;
  buf->maxsize = maxsize;
  buf->delete_on_close = delete_on_close;
  buf->spill_all_contents = spill_all_contents;
  buf->dirpath = dirpath;
}