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
struct TYPE_6__ {int /*<<< orphan*/  repos_node_status; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct status_baton {int /*<<< orphan*/  real_status_baton; int /*<<< orphan*/ * (* real_status_func ) (int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_dup_status3 (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_status_deleted ; 

__attribute__((used)) static svn_error_t *
mark_deleted(void *baton,
             const char *local_abspath,
             const svn_wc_status3_t *status,
             apr_pool_t *scratch_pool)
{
  struct status_baton *sb = baton;
  svn_wc_status3_t *new_status = svn_wc_dup_status3(status, scratch_pool);
  new_status->repos_node_status = svn_wc_status_deleted;
  return sb->real_status_func(sb->real_status_baton, local_abspath,
                              new_status, scratch_pool);
}