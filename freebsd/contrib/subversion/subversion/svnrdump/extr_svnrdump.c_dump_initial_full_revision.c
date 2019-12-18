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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* finish_report ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_path ) (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_cancel ; 
 int /*<<< orphan*/  dump_revision_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_ra_do_update3 (int /*<<< orphan*/ *,TYPE_1__ const**,void**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_path_relative_to_root (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_rdump__get_dump_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
dump_initial_full_revision(svn_ra_session_t *session,
                           svn_ra_session_t *extra_ra_session,
                           svn_stream_t *stdout_stream,
                           svn_revnum_t revision,
                           svn_boolean_t quiet,
                           apr_pool_t *pool)
{
  const svn_ra_reporter3_t *reporter;
  void *report_baton;
  const svn_delta_editor_t *dump_editor;
  void *dump_baton;
  const char *session_url, *source_relpath;

  /* Determine whether we're dumping the repository root URL or some
     child thereof.  If we're dumping a subtree of the repository
     rather than the root, we have to jump through some hoops to make
     our update-driven dump generation work the way a replay-driven
     one would.

     See http://subversion.tigris.org/issues/show_bug.cgi?id=4101
  */
  SVN_ERR(svn_ra_get_session_url(session, &session_url, pool));
  SVN_ERR(svn_ra_get_path_relative_to_root(session, &source_relpath,
                                           session_url, pool));

  /* Start with a revision record header. */
  SVN_ERR(dump_revision_header(session, stdout_stream, revision, pool));

  /* Then, we'll drive the dump editor with what would look like a
     full checkout of the repository as it looked in START_REVISION.
     We do this by manufacturing a basic 'report' to the update
     reporter, telling it that we have nothing to start with.  The
     delta between nothing and everything-at-REV is, effectively, a
     full dump of REV. */
  SVN_ERR(svn_rdump__get_dump_editor(&dump_editor, &dump_baton, revision,
                                     stdout_stream, extra_ra_session,
                                     source_relpath, check_cancel, NULL, pool));
  SVN_ERR(svn_ra_do_update3(session, &reporter, &report_baton, revision,
                            "", svn_depth_infinity, FALSE, FALSE,
                            dump_editor, dump_baton, pool, pool));
  SVN_ERR(reporter->set_path(report_baton, "", revision,
                             svn_depth_infinity, TRUE, NULL, pool));
  SVN_ERR(reporter->finish_report(report_baton, pool));

  /* All finished with START_REVISION! */
  if (! quiet)
    SVN_ERR(svn_cmdline_fprintf(stderr, pool, "* Dumped revision %lu.\n",
                                revision));

  return SVN_NO_ERROR;
}