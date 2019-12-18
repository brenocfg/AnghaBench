#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_14__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_2__ svn_ra_svn__session_baton_t ;
struct TYPE_13__ {int /*<<< orphan*/  list; } ;
struct TYPE_15__ {scalar_t__ kind; TYPE_1__ u; } ;
typedef  TYPE_3__ svn_ra_svn__item_t ;
struct TYPE_16__ {TYPE_2__* priv; } ;
typedef  TYPE_4__ svn_ra_session_t ;
struct TYPE_17__ {char const* path; void* range_end; void* range_start; } ;
typedef  TYPE_5__ svn_location_segment_t ;
typedef  int /*<<< orphan*/  (* svn_location_segment_receiver_t ) (TYPE_5__*,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_CEASE_INVOCATION ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_MALFORMED_DATA ; 
 scalar_t__ SVN_IS_VALID_REVNUM (void*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SVN_LIST ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_5__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * handle_unsupported_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_done_response (TYPE_3__*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_error_find_cause (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,void**,void**,char const**) ; 
 int /*<<< orphan*/ * svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_ra_svn__read_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/ * svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char const*,void*,void*,void*) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
perform_get_location_segments(svn_error_t **outer_error,
                              svn_ra_session_t *session,
                              const char *path,
                              svn_revnum_t peg_revision,
                              svn_revnum_t start_rev,
                              svn_revnum_t end_rev,
                              svn_location_segment_receiver_t receiver,
                              void *receiver_baton,
                              apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess_baton = session->priv;
  svn_ra_svn_conn_t *conn = sess_baton->conn;
  svn_boolean_t is_done;
  apr_pool_t *iterpool = svn_pool_create(pool);

  /* Transmit the parameters. */
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "w(c(?r)(?r)(?r))",
                                  "get-location-segments",
                                  path, peg_revision, start_rev, end_rev));

  /* Servers before 1.5 don't support this command. Check for this here. */
  SVN_ERR(handle_unsupported_cmd(handle_auth_request(sess_baton, pool),
                                 N_("'get-location-segments'"
                                    " not implemented")));

  /* Parse the response. */
  is_done = FALSE;
  while (!is_done)
    {
      svn_revnum_t range_start, range_end;
      svn_ra_svn__item_t *item;
      const char *ret_path;

      svn_pool_clear(iterpool);
      SVN_ERR(svn_ra_svn__read_item(conn, iterpool, &item));
      if (is_done_response(item))
        is_done = 1;
      else if (item->kind != SVN_RA_SVN_LIST)
        return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                _("Location segment entry not a list"));
      else
        {
          svn_location_segment_t *segment = apr_pcalloc(iterpool,
                                                        sizeof(*segment));
          SVN_ERR(svn_ra_svn__parse_tuple(&item->u.list, "rr(?c)",
                                          &range_start, &range_end, &ret_path));
          if (! (SVN_IS_VALID_REVNUM(range_start)
                 && SVN_IS_VALID_REVNUM(range_end)))
            return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                    _("Expected valid revision range"));
          if (ret_path)
            ret_path = svn_relpath_canonicalize(ret_path, iterpool);
          segment->path = ret_path;
          segment->range_start = range_start;
          segment->range_end = range_end;

          if (!*outer_error)
            {
              svn_error_t *err = svn_error_trace(receiver(segment, receiver_baton,
                                                          iterpool));

              if (svn_error_find_cause(err, SVN_ERR_CEASE_INVOCATION))
                *outer_error = err;
              else
                SVN_ERR(err);
            }
        }
    }
  svn_pool_destroy(iterpool);

  /* Read the response. This is so the server would have a chance to
   * report an error. */
  SVN_ERR(svn_ra_svn__read_cmd_response(conn, pool, ""));

  return SVN_NO_ERROR;
}