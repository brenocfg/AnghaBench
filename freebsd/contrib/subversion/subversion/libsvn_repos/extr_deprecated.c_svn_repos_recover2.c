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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_repos_recover3 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ * (*) (void*),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_recover2(const char *path,
                   svn_boolean_t nonblocking,
                   svn_error_t *(*start_callback)(void *baton),
                   void *start_callback_baton,
                   apr_pool_t *pool)
{
  return svn_repos_recover3(path, nonblocking,
                            start_callback, start_callback_baton,
                            NULL, NULL,
                            pool);
}