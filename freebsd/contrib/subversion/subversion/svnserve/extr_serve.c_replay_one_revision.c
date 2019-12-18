#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* abort_edit ) (void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_15__ {TYPE_2__* repository; } ;
typedef  TYPE_4__ server_baton_t ;
struct TYPE_16__ {int /*<<< orphan*/ * conn; TYPE_4__* server; } ;
typedef  TYPE_5__ authz_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {TYPE_1__* fs_path; int /*<<< orphan*/  fs; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authz_check_access_cb_func (TYPE_4__*) ; 
 int /*<<< orphan*/  log_command (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_log__replay (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn__write_cmd_finish_replay (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn_get_editor (TYPE_3__ const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_replay2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__ const*,void*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *replay_one_revision(svn_ra_svn_conn_t *conn,
                                        server_baton_t *b,
                                        svn_revnum_t rev,
                                        svn_revnum_t low_water_mark,
                                        svn_boolean_t send_deltas,
                                        apr_pool_t *pool)
{
  const svn_delta_editor_t *editor;
  void *edit_baton;
  svn_fs_root_t *root;
  svn_error_t *err;
  authz_baton_t ab;

  ab.server = b;
  ab.conn = conn;

  SVN_ERR(log_command(b, conn, pool,
                      svn_log__replay(b->repository->fs_path->data, rev,
                                      pool)));

  svn_ra_svn_get_editor(&editor, &edit_baton, conn, pool, NULL, NULL);

  err = svn_fs_revision_root(&root, b->repository->fs, rev, pool);

  if (! err)
    err = svn_repos_replay2(root, b->repository->fs_path->data,
                            low_water_mark, send_deltas, editor, edit_baton,
                            authz_check_access_cb_func(b), &ab, pool);

  if (err)
    svn_error_clear(editor->abort_edit(edit_baton, pool));
  SVN_CMD_ERR(err);

  return svn_ra_svn__write_cmd_finish_replay(conn, pool);
}