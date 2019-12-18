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
typedef  int /*<<< orphan*/  svn_client_list_func_t ;
typedef  int /*<<< orphan*/  svn_client_list_func2_t ;
struct list_func_wrapper_baton {int /*<<< orphan*/  list_func1; void* list_func1_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct list_func_wrapper_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_func_wrapper ; 

__attribute__((used)) static void
wrap_list_func(svn_client_list_func2_t *list_func2,
               void **list_func2_baton,
               svn_client_list_func_t list_func,
               void *baton,
               apr_pool_t *result_pool)
{
  struct list_func_wrapper_baton *lfwb = apr_palloc(result_pool,
                                                    sizeof(*lfwb));

  /* Set the user provided old format callback in the baton. */
  lfwb->list_func1_baton = baton;
  lfwb->list_func1 = list_func;

  *list_func2_baton = lfwb;
  *list_func2 = list_func_wrapper;
}