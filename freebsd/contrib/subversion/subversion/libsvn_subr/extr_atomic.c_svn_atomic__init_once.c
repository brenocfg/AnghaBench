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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_atomic_t ;
typedef  int /*<<< orphan*/  svn_atomic__err_init_func_t ;
struct TYPE_3__ {int /*<<< orphan*/ * err; void* baton; int /*<<< orphan*/ * pool; int /*<<< orphan*/  err_init_func; } ;
typedef  TYPE_1__ init_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ATOMIC_INIT_FAILURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  err_init_func_wrapper ; 
 scalar_t__ init_once (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

svn_error_t *
svn_atomic__init_once(volatile svn_atomic_t *global_status,
                      svn_atomic__err_init_func_t err_init_func,
                      void *baton,
                      apr_pool_t* pool)
{
  init_baton_t init_baton;
  init_baton.err_init_func = err_init_func;
  init_baton.err = NULL;
  init_baton.pool = pool;
  init_baton.baton = baton;

  if (init_once(global_status, err_init_func_wrapper, &init_baton))
    return SVN_NO_ERROR;

  return svn_error_create(SVN_ERR_ATOMIC_INIT_FAILURE, init_baton.err,
                          "Couldn't perform atomic initialization");
}