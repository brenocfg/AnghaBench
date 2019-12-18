#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
struct TYPE_6__ {void* edit_baton; int /*<<< orphan*/  const* editor; int /*<<< orphan*/ * pool; int /*<<< orphan*/  conn; TYPE_1__* sess_baton; } ;
typedef  TYPE_2__ ra_svn_reporter_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SVN_CAP_DEPTH ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ra_svn_reporter ; 
 int /*<<< orphan*/  svn_delta_depth_filter_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_files ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_ra_svn_has_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ra_svn_get_reporter(svn_ra_svn__session_baton_t *sess_baton,
                    apr_pool_t *pool,
                    const svn_delta_editor_t *editor,
                    void *edit_baton,
                    const char *target,
                    svn_depth_t depth,
                    const svn_ra_reporter3_t **reporter,
                    void **report_baton)
{
  ra_svn_reporter_baton_t *b;
  const svn_delta_editor_t *filter_editor;
  void *filter_baton;

  /* We can skip the depth filtering when the user requested
     depth_files or depth_infinity because the server will
     transmit the right stuff anyway. */
  if ((depth != svn_depth_files) && (depth != svn_depth_infinity)
      && ! svn_ra_svn_has_capability(sess_baton->conn, SVN_RA_SVN_CAP_DEPTH))
    {
      SVN_ERR(svn_delta_depth_filter_editor(&filter_editor,
                                            &filter_baton,
                                            editor, edit_baton, depth,
                                            *target != '\0',
                                            pool));
      editor = filter_editor;
      edit_baton = filter_baton;
    }

  b = apr_palloc(pool, sizeof(*b));
  b->sess_baton = sess_baton;
  b->conn = sess_baton->conn;
  b->pool = pool;
  b->editor = editor;
  b->edit_baton = edit_baton;

  *reporter = &ra_svn_reporter;
  *report_baton = b;

  return SVN_NO_ERROR;
}