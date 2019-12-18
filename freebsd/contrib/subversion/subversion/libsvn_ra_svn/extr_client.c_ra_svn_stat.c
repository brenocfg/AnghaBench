#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_9__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
struct TYPE_10__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {char const* last_author; int /*<<< orphan*/  time; int /*<<< orphan*/  created_rev; int /*<<< orphan*/  has_props; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; } ;
typedef  TYPE_3__ svn_dirent_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_unsupported_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* reparent_path (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_dirent_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_kind_from_word (char const*) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_stat(svn_ra_session_t *session,
                                const char *path, svn_revnum_t rev,
                                svn_dirent_t **dirent, apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess_baton = session->priv;
  svn_ra_svn_conn_t *conn = sess_baton->conn;
  svn_ra_svn__list_t *list = NULL;
  svn_dirent_t *the_dirent;

  path = reparent_path(session, path, pool);
  SVN_ERR(svn_ra_svn__write_cmd_stat(conn, pool, path, rev));
  SVN_ERR(handle_unsupported_cmd(handle_auth_request(sess_baton, pool),
                                 N_("'stat' not implemented")));
  SVN_ERR(svn_ra_svn__read_cmd_response(conn, pool, "(?l)", &list));

  if (! list)
    {
      *dirent = NULL;
    }
  else
    {
      const char *kind, *cdate, *cauthor;
      svn_boolean_t has_props;
      svn_revnum_t crev;
      apr_uint64_t size;

      SVN_ERR(svn_ra_svn__parse_tuple(list, "wnbr(?c)(?c)",
                                      &kind, &size, &has_props,
                                      &crev, &cdate, &cauthor));

      the_dirent = svn_dirent_create(pool);
      the_dirent->kind = svn_node_kind_from_word(kind);
      the_dirent->size = size;/* FIXME: svn_filesize_t */
      the_dirent->has_props = has_props;
      the_dirent->created_rev = crev;
      SVN_ERR(svn_time_from_cstring(&the_dirent->time, cdate, pool));
      the_dirent->last_author = cauthor;

      *dirent = the_dirent;
    }

  return SVN_NO_ERROR;
}