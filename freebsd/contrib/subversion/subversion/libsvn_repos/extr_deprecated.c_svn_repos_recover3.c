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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct recover_baton {void* start_callback_baton; int /*<<< orphan*/ * (* start_callback ) (void*) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  recovery_started ; 
 int /*<<< orphan*/ * svn_repos_recover4 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct recover_baton*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_recover3(const char *path,
                   svn_boolean_t nonblocking,
                   svn_error_t *(*start_callback)(void *baton),
                   void *start_callback_baton,
                   svn_cancel_func_t cancel_func, void *cancel_baton,
                   apr_pool_t *pool)
{
  struct recover_baton rb;

  rb.start_callback = start_callback;
  rb.start_callback_baton = start_callback_baton;

  return svn_repos_recover4(path, nonblocking, recovery_started, &rb,
                            cancel_func, cancel_baton, pool);
}