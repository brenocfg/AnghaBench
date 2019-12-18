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
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ fs_fs_dag_cache_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 

fs_fs_dag_cache_t*
svn_fs_fs__create_dag_cache(apr_pool_t *pool)
{
  fs_fs_dag_cache_t *result = apr_pcalloc(pool, sizeof(*result));
  result->pool = svn_pool_create(pool);

  return result;
}