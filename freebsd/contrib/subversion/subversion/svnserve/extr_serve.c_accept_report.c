#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int svn_boolean_t ;
struct TYPE_12__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
struct TYPE_13__ {int entry_counter; scalar_t__ only_empty_entries; int /*<<< orphan*/ * err; int /*<<< orphan*/ * from_rev; void* report_baton; int /*<<< orphan*/  repos_url; TYPE_3__* sb; } ;
typedef  TYPE_4__ report_driver_baton_t ;
struct TYPE_14__ {int /*<<< orphan*/ * conn; TYPE_3__* server; } ;
typedef  TYPE_5__ authz_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  repos_url; TYPE_1__* fs_path; int /*<<< orphan*/  repos; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  authz_check_access_cb_func (TYPE_3__*) ; 
 int /*<<< orphan*/  report_commands ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_uri_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn__handle_commands2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn_get_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn_zero_copy_limit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_begin_report3 (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *accept_report(svn_boolean_t *only_empty_entry,
                                  svn_revnum_t *from_rev,
                                  svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                                  server_baton_t *b, svn_revnum_t rev,
                                  const char *target, const char *tgt_path,
                                  svn_boolean_t text_deltas,
                                  svn_depth_t depth,
                                  svn_boolean_t send_copyfrom_args,
                                  svn_boolean_t ignore_ancestry)
{
  const svn_delta_editor_t *editor;
  void *edit_baton, *report_baton;
  report_driver_baton_t rb;
  svn_error_t *err;
  authz_baton_t ab;

  ab.server = b;
  ab.conn = conn;

  /* Make an svn_repos report baton.  Tell it to drive the network editor
   * when the report is complete. */
  svn_ra_svn_get_editor(&editor, &edit_baton, conn, pool, NULL, NULL);
  SVN_CMD_ERR(svn_repos_begin_report3(&report_baton, rev,
                                      b->repository->repos,
                                      b->repository->fs_path->data, target,
                                      tgt_path, text_deltas, depth,
                                      ignore_ancestry, send_copyfrom_args,
                                      editor, edit_baton,
                                      authz_check_access_cb_func(b),
                                      &ab, svn_ra_svn_zero_copy_limit(conn),
                                      pool));

  rb.sb = b;
  rb.repos_url = svn_path_uri_decode(b->repository->repos_url, pool);
  rb.report_baton = report_baton;
  rb.err = NULL;
  rb.entry_counter = 0;
  rb.only_empty_entries = TRUE;
  rb.from_rev = from_rev;
  if (from_rev)
    *from_rev = SVN_INVALID_REVNUM;
  err = svn_ra_svn__handle_commands2(conn, pool, report_commands, &rb, TRUE);
  if (err)
    {
      /* Network or protocol error while handling commands. */
      svn_error_clear(rb.err);
      return err;
    }
  else if (rb.err)
    {
      /* Some failure during the reporting or editing operations. */
      SVN_CMD_ERR(rb.err);
    }
  SVN_ERR(svn_ra_svn__write_cmd_response(conn, pool, ""));

  if (only_empty_entry)
    *only_empty_entry = rb.entry_counter == 1 && rb.only_empty_entries;

  return SVN_NO_ERROR;
}