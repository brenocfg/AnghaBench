#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* file; void* message; int /*<<< orphan*/ * pool; struct TYPE_6__* child; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  abort () ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  err_abort ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_error_dup(const svn_error_t *err)
{
  apr_pool_t *pool;
  svn_error_t *new_err = NULL, *tmp_err = NULL;

  if (!err)
    return SVN_NO_ERROR;

  pool = svn_pool_create(NULL);
  if (!pool)
    abort();

  for (; err; err = err->child)
    {
      if (! new_err)
        {
          new_err = apr_palloc(pool, sizeof(*new_err));
          tmp_err = new_err;
        }
      else
        {
          tmp_err->child = apr_palloc(pool, sizeof(*tmp_err->child));
          tmp_err = tmp_err->child;
        }
      *tmp_err = *err;
      tmp_err->pool = pool;
      if (tmp_err->message)
        tmp_err->message = apr_pstrdup(pool, tmp_err->message);
      if (tmp_err->file)
        tmp_err->file = apr_pstrdup(pool, tmp_err->file);
    }

#if defined(SVN_DEBUG)
  apr_pool_cleanup_register(pool, tmp_err,
                            err_abort,
                            apr_pool_cleanup_null);
#endif

  return new_err;
}