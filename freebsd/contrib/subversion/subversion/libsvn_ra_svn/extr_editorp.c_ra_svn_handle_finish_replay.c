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
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/ * aborted; int /*<<< orphan*/  done; int /*<<< orphan*/  for_replay; } ;
typedef  TYPE_1__ ra_svn_driver_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_UNKNOWN_CMD ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ra_svn_handle_finish_replay(svn_ra_svn_conn_t *conn,
                            apr_pool_t *pool,
                            const svn_ra_svn__list_t *params,
                            ra_svn_driver_state_t *ds)
{
  if (!ds->for_replay)
    return svn_error_createf
      (SVN_ERR_RA_SVN_UNKNOWN_CMD, NULL,
       _("Command 'finish-replay' invalid outside of replays"));
  ds->done = TRUE;
  if (ds->aborted)
    *ds->aborted = FALSE;
  return SVN_NO_ERROR;
}