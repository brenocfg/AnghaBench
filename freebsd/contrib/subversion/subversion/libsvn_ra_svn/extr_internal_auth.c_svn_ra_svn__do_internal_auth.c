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
struct TYPE_4__ {int /*<<< orphan*/  auth_baton; scalar_t__ is_tunneled; int /*<<< orphan*/  realm_prefix; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_auth_iterstate_t ;
struct TYPE_5__ {char* username; char* password; } ;
typedef  TYPE_2__ svn_auth_cred_simple_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_CRED_SIMPLE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_NOT_AUTHORIZED ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_NO_MECHANISMS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * read_success (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth_first_credentials (void**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth_next_credentials (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth_save_credentials (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_ra_svn__auth_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__cram_client (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const**) ; 
 scalar_t__ svn_ra_svn__find_mech (int /*<<< orphan*/  const*,char*) ; 

svn_error_t *
svn_ra_svn__do_internal_auth(svn_ra_svn__session_baton_t *sess,
                             const svn_ra_svn__list_t *mechlist,
                             const char *realm, apr_pool_t *pool)
{
  svn_ra_svn_conn_t *conn = sess->conn;
  const char *realmstring, *user, *password, *msg;
  svn_auth_iterstate_t *iterstate;
  void *creds;

  realmstring = apr_psprintf(pool, "%s %s", sess->realm_prefix, realm);

  if (sess->is_tunneled && svn_ra_svn__find_mech(mechlist, "EXTERNAL"))
    {
        /* Ask the server to use the tunnel connection environment (on
        * Unix, that means uid) to determine the authentication name. */
      SVN_ERR(svn_ra_svn__auth_response(conn, pool, "EXTERNAL", ""));
      return read_success(conn, pool);
    }
  else if (svn_ra_svn__find_mech(mechlist, "ANONYMOUS"))
    {
      SVN_ERR(svn_ra_svn__auth_response(conn, pool, "ANONYMOUS", ""));
      return read_success(conn, pool);
    }
  else if (svn_ra_svn__find_mech(mechlist, "CRAM-MD5"))
    {
      SVN_ERR(svn_auth_first_credentials(&creds, &iterstate,
                                         SVN_AUTH_CRED_SIMPLE, realmstring,
                                         sess->auth_baton, pool));
      if (!creds)
        return svn_error_create(SVN_ERR_RA_NOT_AUTHORIZED, NULL,
                                _("Can't get password"));
      while (creds)
        {
          user = ((svn_auth_cred_simple_t *) creds)->username;
          password = ((svn_auth_cred_simple_t *) creds)->password;
          SVN_ERR(svn_ra_svn__auth_response(conn, pool, "CRAM-MD5", NULL));
          SVN_ERR(svn_ra_svn__cram_client(conn, pool, user, password, &msg));
          if (!msg)
            break;
          SVN_ERR(svn_auth_next_credentials(&creds, iterstate, pool));
        }
      if (!creds)
        return svn_error_createf(SVN_ERR_RA_NOT_AUTHORIZED, NULL,
                                _("Authentication error from server: %s"),
                                msg);
      SVN_ERR(svn_auth_save_credentials(iterstate, pool));
      return SVN_NO_ERROR;
    }
  else
    return svn_error_create(SVN_ERR_RA_SVN_NO_MECHANISMS, NULL, NULL);
}