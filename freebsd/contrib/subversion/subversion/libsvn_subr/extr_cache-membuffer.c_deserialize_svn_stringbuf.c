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
struct TYPE_3__ {void* len; void* data; void* blocksize; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
deserialize_svn_stringbuf(void **item,
                          void *buffer,
                          apr_size_t buffer_size,
                          apr_pool_t *result_pool)
{
  svn_stringbuf_t *value_str = apr_palloc(result_pool, sizeof(svn_stringbuf_t));

  value_str->pool = result_pool;
  value_str->blocksize = buffer_size;
  value_str->data = buffer;
  value_str->len = buffer_size-1;
  *item = value_str;

  return SVN_NO_ERROR;
}