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
struct TYPE_3__ {int node_status; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct dir_delete_baton_t {int /*<<< orphan*/  found_edit; int /*<<< orphan*/  compared_abspaths; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CEASE_INVOCATION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
#define  svn_wc_status_deleted 130 
#define  svn_wc_status_ignored 129 
#define  svn_wc_status_none 128 

__attribute__((used)) static svn_error_t *
verify_touched_by_del_check(void *baton,
                            const char *local_abspath,
                            const svn_wc_status3_t *status,
                            apr_pool_t *scratch_pool)
{
  struct dir_delete_baton_t *delb = baton;

  if (svn_hash_gets(delb->compared_abspaths, local_abspath))
    return SVN_NO_ERROR;

  switch (status->node_status)
    {
      case svn_wc_status_deleted:
      case svn_wc_status_ignored:
      case svn_wc_status_none:
        return SVN_NO_ERROR;

      default:
        delb->found_edit = TRUE;
        return svn_error_create(SVN_ERR_CEASE_INVOCATION, NULL, NULL);
    }
}