#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/ * aborted; int /*<<< orphan*/  tokens; int /*<<< orphan*/  done; int /*<<< orphan*/  edit_baton; TYPE_1__* editor; } ;
typedef  TYPE_2__ ra_svn_driver_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* close_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_INCORRECT_EDITOR_COMPLETION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_ra_svn__write_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *
ra_svn_handle_close_edit(svn_ra_svn_conn_t *conn,
                         apr_pool_t *pool,
                         const svn_ra_svn__list_t *params,
                         ra_svn_driver_state_t *ds)
{
  SVN_CMD_ERR(ds->editor->close_edit(ds->edit_baton, pool));
  ds->done = TRUE;
#ifdef SVN_DEBUG
  /* Before enabling this in non-maintainer mode:
     *  Note that this code is used on both client *and* server */
  if (apr_hash_count(ds->tokens) != 0)
    return svn_error_create(
              SVN_ERR_FS_INCORRECT_EDITOR_COMPLETION, NULL,
              _("Closing editor with directories or files open"));
#endif
  if (ds->aborted)
    *ds->aborted = FALSE;
  return svn_ra_svn__write_cmd_response(conn, pool, "");
}