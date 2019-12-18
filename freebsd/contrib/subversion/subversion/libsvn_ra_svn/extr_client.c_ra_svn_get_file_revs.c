#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_13__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_3__ svn_ra_svn__session_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_1__ string; int /*<<< orphan*/  list; } ;
struct TYPE_14__ {scalar_t__ kind; TYPE_2__ u; } ;
typedef  TYPE_4__ svn_ra_svn__item_t ;
struct TYPE_15__ {TYPE_3__* priv; } ;
typedef  TYPE_5__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  (* svn_file_rev_handler_t ) (void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SVN_LIST ; 
 scalar_t__ SVN_RA_SVN_STRING ; 
 scalar_t__ SVN_RA_SVN_UNSPECIFIED_NUMBER ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_unsupported_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_done_response (TYPE_4__*) ; 
 int /*<<< orphan*/  parse_prop_diffs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* reparent_path (TYPE_5__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_delta_noop_window_handler ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_fspath__canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__read_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_get_file_revs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * svn_txdelta_parse_svndiff (scalar_t__,void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_get_file_revs(svn_ra_session_t *session,
                                         const char *path,
                                         svn_revnum_t start, svn_revnum_t end,
                                         svn_boolean_t include_merged_revisions,
                                         svn_file_rev_handler_t handler,
                                         void *handler_baton, apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess_baton = session->priv;
  apr_pool_t *rev_pool, *chunk_pool;
  svn_boolean_t has_txdelta;
  svn_boolean_t had_revision = FALSE;

  /* One sub-pool for each revision and one for each txdelta chunk.
     Note that the rev_pool must live during the following txdelta. */
  rev_pool = svn_pool_create(pool);
  chunk_pool = svn_pool_create(pool);

  path = reparent_path(session, path, pool);
  SVN_ERR(svn_ra_svn__write_cmd_get_file_revs(sess_baton->conn, pool,
                                              path, start, end,
                                              include_merged_revisions));

  /* Servers before 1.1 don't support this command.  Check for this here. */
  SVN_ERR(handle_unsupported_cmd(handle_auth_request(sess_baton, pool),
                                 N_("'get-file-revs' not implemented")));

  while (1)
    {
      svn_ra_svn__list_t *rev_proplist, *proplist;
      apr_uint64_t merged_rev_param;
      apr_array_header_t *props;
      svn_ra_svn__item_t *item;
      apr_hash_t *rev_props;
      svn_revnum_t rev;
      const char *p;
      svn_boolean_t merged_rev;
      svn_txdelta_window_handler_t d_handler;
      void *d_baton;

      svn_pool_clear(rev_pool);
      svn_pool_clear(chunk_pool);
      SVN_ERR(svn_ra_svn__read_item(sess_baton->conn, rev_pool, &item));
      if (is_done_response(item))
        break;
      /* Either we've got a correct revision or we will error out below. */
      had_revision = TRUE;
      if (item->kind != SVN_RA_SVN_LIST)
        return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                _("Revision entry not a list"));

      SVN_ERR(svn_ra_svn__parse_tuple(&item->u.list,
                                      "crll?B", &p, &rev, &rev_proplist,
                                      &proplist, &merged_rev_param));
      p = svn_fspath__canonicalize(p, rev_pool);
      SVN_ERR(svn_ra_svn__parse_proplist(rev_proplist, rev_pool, &rev_props));
      SVN_ERR(parse_prop_diffs(proplist, rev_pool, &props));
      if (merged_rev_param == SVN_RA_SVN_UNSPECIFIED_NUMBER)
        merged_rev = FALSE;
      else
        merged_rev = (svn_boolean_t) merged_rev_param;

      /* Get the first delta chunk so we know if there is a delta. */
      SVN_ERR(svn_ra_svn__read_item(sess_baton->conn, chunk_pool, &item));
      if (item->kind != SVN_RA_SVN_STRING)
        return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                _("Text delta chunk not a string"));
      has_txdelta = item->u.string.len > 0;

      SVN_ERR(handler(handler_baton, p, rev, rev_props, merged_rev,
                      has_txdelta ? &d_handler : NULL, &d_baton,
                      props, rev_pool));

      /* Process the text delta if any. */
      if (has_txdelta)
        {
          svn_stream_t *stream;

          if (d_handler && d_handler != svn_delta_noop_window_handler)
            stream = svn_txdelta_parse_svndiff(d_handler, d_baton, TRUE,
                                               rev_pool);
          else
            stream = NULL;
          while (item->u.string.len > 0)
            {
              apr_size_t size;

              size = item->u.string.len;
              if (stream)
                SVN_ERR(svn_stream_write(stream, item->u.string.data, &size));
              svn_pool_clear(chunk_pool);

              SVN_ERR(svn_ra_svn__read_item(sess_baton->conn, chunk_pool,
                                            &item));
              if (item->kind != SVN_RA_SVN_STRING)
                return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                        _("Text delta chunk not a string"));
            }
          if (stream)
            SVN_ERR(svn_stream_close(stream));
        }
    }

  SVN_ERR(svn_ra_svn__read_cmd_response(sess_baton->conn, pool, ""));

  /* Return error if we didn't get any revisions. */
  if (!had_revision)
    return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                            _("The get-file-revs command didn't return "
                              "any revisions"));

  svn_pool_destroy(chunk_pool);
  svn_pool_destroy(rev_pool);

  return SVN_NO_ERROR;
}