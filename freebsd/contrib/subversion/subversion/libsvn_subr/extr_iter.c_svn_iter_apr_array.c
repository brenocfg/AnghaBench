#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* (* svn_iter_apr_array_cb_t ) (void*,void*,int /*<<< orphan*/ *) ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {int nelts; int elt_size; void* elts; } ;
typedef  TYPE_3__ apr_array_header_t ;

/* Variables and functions */
 scalar_t__ SVN_ERR_ITER_BREAK ; 
 TYPE_1__* SVN_NO_ERROR ; 
 TYPE_1__ internal_break_error ; 
 TYPE_1__* stub1 (void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_iter_apr_array(svn_boolean_t *completed,
                   const apr_array_header_t *array,
                   svn_iter_apr_array_cb_t func,
                   void *baton,
                   apr_pool_t *pool)
{
  svn_error_t *err = SVN_NO_ERROR;
  apr_pool_t *iterpool = svn_pool_create(pool);
  int i;

  for (i = 0; (! err) && i < array->nelts; ++i)
    {
      void *item = array->elts + array->elt_size*i;

      svn_pool_clear(iterpool);

      err = (*func)(baton, item, iterpool);
    }

  if (completed)
    *completed = ! err;

  if (err && err->apr_err == SVN_ERR_ITER_BREAK)
    {
      if (err != &internal_break_error)
        /* Errors - except those created by svn_iter_break() -
           need to be cleared when not further propagated. */
        svn_error_clear(err);

      err = SVN_NO_ERROR;
    }

  /* Clear iterpool, because callers may clear the error but have no way
     to clear the iterpool with potentially lots of allocated memory */
  svn_pool_destroy(iterpool);

  return err;
}