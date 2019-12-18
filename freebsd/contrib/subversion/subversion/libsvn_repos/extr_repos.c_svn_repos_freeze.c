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
typedef  int /*<<< orphan*/  svn_repos_freeze_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct freeze_baton_t {int /*<<< orphan*/  scratch_pool; void* freeze_baton; int /*<<< orphan*/  freeze_func; scalar_t__ counter; int /*<<< orphan*/ * paths; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  multi_freeze (struct freeze_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_repos_freeze(apr_array_header_t *paths,
                 svn_repos_freeze_func_t freeze_func,
                 void *freeze_baton,
                 apr_pool_t *pool)
{
  struct freeze_baton_t fb;

  fb.paths = paths;
  fb.counter = 0;
  fb.freeze_func = freeze_func;
  fb.freeze_baton = freeze_baton;
  fb.scratch_pool = svn_pool_create(pool);

  SVN_ERR(multi_freeze(&fb, pool));

  svn_pool_destroy(fb.scratch_pool);
  return SVN_NO_ERROR;
}