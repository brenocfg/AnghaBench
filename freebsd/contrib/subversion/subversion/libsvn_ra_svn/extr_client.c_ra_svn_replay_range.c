#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_6__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
struct TYPE_7__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  (* svn_ra_replay_revstart_callback_t ) (scalar_t__,void*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  (* svn_ra_replay_revfinish_callback_t ) (scalar_t__,void*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_EDIT_ABORTED ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_MALFORMED_DATA ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ensure_exact_server_parent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_unsupported_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__handle_failure_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__read_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_replay_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn_drive_editor2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ra_svn_replay_range(svn_ra_session_t *session,
                    svn_revnum_t start_revision,
                    svn_revnum_t end_revision,
                    svn_revnum_t low_water_mark,
                    svn_boolean_t send_deltas,
                    svn_ra_replay_revstart_callback_t revstart_func,
                    svn_ra_replay_revfinish_callback_t revfinish_func,
                    void *replay_baton,
                    apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess = session->priv;
  apr_pool_t *iterpool;
  svn_revnum_t rev;
  svn_boolean_t drive_aborted = FALSE;

  /* Complex EDITOR callbacks may rely on client and server parent path
     being in sync. */
  SVN_ERR(ensure_exact_server_parent(session, pool));
  SVN_ERR(svn_ra_svn__write_cmd_replay_range(sess->conn, pool,
                                             start_revision, end_revision,
                                             low_water_mark, send_deltas));

  SVN_ERR(handle_unsupported_cmd(handle_auth_request(sess, pool),
                                 N_("Server doesn't support the "
                                    "replay-range command")));

  iterpool = svn_pool_create(pool);
  for (rev = start_revision; rev <= end_revision; rev++)
    {
      const svn_delta_editor_t *editor;
      void *edit_baton;
      apr_hash_t *rev_props;
      const char *word;
      svn_ra_svn__list_t *list;

      svn_pool_clear(iterpool);

      SVN_ERR(svn_ra_svn__read_tuple(sess->conn, iterpool,
                                     "wl", &word, &list));

      if (strcmp(word, "revprops") != 0)
        {
          if (strcmp(word, "failure") == 0)
            SVN_ERR(svn_ra_svn__handle_failure_status(list));

          return svn_error_createf(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                   _("Expected 'revprops', found '%s'"),
                                   word);
        }

      SVN_ERR(svn_ra_svn__parse_proplist(list, iterpool, &rev_props));

      SVN_ERR(revstart_func(rev, replay_baton,
                            &editor, &edit_baton,
                            rev_props,
                            iterpool));
      SVN_ERR(svn_ra_svn_drive_editor2(sess->conn, iterpool,
                                       editor, edit_baton,
                                       &drive_aborted, TRUE));
      /* If drive_editor2() aborted the commit, do NOT try to call
         revfinish_func and commit the transaction! */
      if (drive_aborted) {
        svn_pool_destroy(iterpool);
        return svn_error_create(SVN_ERR_RA_SVN_EDIT_ABORTED, NULL,
                                _("Error while replaying commit"));
      }
      SVN_ERR(revfinish_func(rev, replay_baton,
                             editor, edit_baton,
                             rev_props,
                             iterpool));
    }
  svn_pool_destroy(iterpool);

  return svn_error_trace(svn_ra_svn__read_cmd_response(sess->conn, pool, ""));
}