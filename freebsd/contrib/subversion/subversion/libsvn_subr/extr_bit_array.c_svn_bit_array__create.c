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
struct TYPE_3__ {int block_count; void* blocks; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_bit_array__t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int select_data_size (int /*<<< orphan*/ ) ; 

svn_bit_array__t *
svn_bit_array__create(apr_size_t max,
                      apr_pool_t *pool)
{
  svn_bit_array__t *array = apr_pcalloc(pool, sizeof(*array));

  array->block_count = select_data_size(max);
  array->pool = pool;
  array->blocks = apr_pcalloc(pool,
                              array->block_count * sizeof(*array->blocks));

  return array;
}