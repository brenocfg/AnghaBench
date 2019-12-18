#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  hex ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_MD5_DIGESTSIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_NOT_AUTHORIZED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 int /*<<< orphan*/  compute_digest (unsigned char*,char const*,char const*) ; 
 int /*<<< orphan*/  hex_encode (char*,unsigned char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__read_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const**,char const**) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

svn_error_t *svn_ra_svn__cram_client(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                                     const char *user, const char *password,
                                     const char **message)
{
  const char *status, *str, *reply;
  unsigned char digest[APR_MD5_DIGESTSIZE];
  char hex[2 * APR_MD5_DIGESTSIZE + 1];

  /* Read the server challenge. */
  SVN_ERR(svn_ra_svn__read_tuple(conn, pool, "w(?c)", &status, &str));
  if (strcmp(status, "failure") == 0 && str)
    {
      *message = str;
      return SVN_NO_ERROR;
    }
  else if (strcmp(status, "step") != 0 || !str)
    return svn_error_create(SVN_ERR_RA_NOT_AUTHORIZED, NULL,
                            _("Unexpected server response to authentication"));

  /* Write our response. */
  compute_digest(digest, str, password);
  hex_encode(hex, digest);
  hex[sizeof(hex) - 1] = '\0';
  reply = apr_psprintf(pool, "%s %s", user, hex);
  SVN_ERR(svn_ra_svn__write_cstring(conn, pool, reply));

  /* Read the success or failure response from the server. */
  SVN_ERR(svn_ra_svn__read_tuple(conn, pool, "w(?c)", &status, &str));
  if (strcmp(status, "failure") == 0 && str)
    {
      *message = str;
      return SVN_NO_ERROR;
    }
  else if (strcmp(status, "success") != 0 || str)
    return svn_error_create(SVN_ERR_RA_NOT_AUTHORIZED, NULL,
                            _("Unexpected server response to authentication"));

  *message = NULL;
  return SVN_NO_ERROR;
}