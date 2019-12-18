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
struct TYPE_5__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  objects; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ svn_object_pool__t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_pool_cleanup ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_object_pool__create(svn_object_pool__t **object_pool,
                        svn_boolean_t thread_safe,
                        apr_pool_t *pool)
{
  svn_object_pool__t *result;

  /* construct the object pool in our private ROOT_POOL to survive POOL
   * cleanup and to prevent threading issues with the allocator
   */
  result = apr_pcalloc(pool, sizeof(*result));
  SVN_ERR(svn_mutex__init(&result->mutex, thread_safe, pool));

  result->pool = pool;
  result->objects = svn_hash__make(result->pool);

  /* make sure we clean up nicely.
   * We need two cleanup functions of which exactly one will be run
   * (disabling the respective other as the first step).  If the owning
   * pool does not cleaned up / destroyed explicitly, it may live longer
   * than our allocator.  So, we need do act upon cleanup requests from
   * either side - owning_pool and root_pool.
   */
  apr_pool_cleanup_register(pool, result, object_pool_cleanup,
                            apr_pool_cleanup_null);

  *object_pool = result;
  return SVN_NO_ERROR;
}