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
typedef  int /*<<< orphan*/  svn_mutex__t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ assume_native_charset_is_utf8 ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_mutex__init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlate_cleanup ; 
 scalar_t__ xlate_handle_hash ; 
 int /*<<< orphan*/ * xlate_handle_mutex ; 

void
svn_utf_initialize2(svn_boolean_t assume_native_utf8,
                    apr_pool_t *pool)
{
  if (!xlate_handle_hash)
    {
      /* We create our own subpool, which we protect with the mutex.
         We can't use the pool passed to us by the caller, since we will
         use it for xlate handle allocations, possibly in multiple threads,
         and pool allocation is not thread-safe. */
      apr_pool_t *subpool = svn_pool_create(pool);
      svn_mutex__t *mutex;
      svn_error_t *err = svn_mutex__init(&mutex, TRUE, subpool);
      if (err)
        {
          svn_error_clear(err);
          return;
        }

      xlate_handle_mutex = mutex;
      xlate_handle_hash = apr_hash_make(subpool);

      apr_pool_cleanup_register(subpool, NULL, xlate_cleanup,
                                apr_pool_cleanup_null);
    }

    if (!assume_native_charset_is_utf8)
      assume_native_charset_is_utf8 = assume_native_utf8;
}