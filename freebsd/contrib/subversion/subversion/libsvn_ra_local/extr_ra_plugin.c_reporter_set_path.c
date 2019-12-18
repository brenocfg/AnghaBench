#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  report_baton; } ;
typedef  TYPE_1__ reporter_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_repos_set_path3 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
reporter_set_path(void *reporter_baton,
                  const char *path,
                  svn_revnum_t revision,
                  svn_depth_t depth,
                  svn_boolean_t start_empty,
                  const char *lock_token,
                  apr_pool_t *pool)
{
  reporter_baton_t *rbaton = reporter_baton;
  return svn_repos_set_path3(rbaton->report_baton, path,
                             revision, depth, start_empty, lock_token, pool);
}