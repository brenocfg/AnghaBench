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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_NOT_AUTHORIZED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_ra_svn__read_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const**,char const**) ; 

__attribute__((used)) static svn_error_t *read_success(svn_ra_svn_conn_t *conn, apr_pool_t *pool)
{
  const char *status, *arg;

  SVN_ERR(svn_ra_svn__read_tuple(conn, pool, "w(?c)", &status, &arg));
  if (strcmp(status, "failure") == 0 && arg)
    return svn_error_createf(SVN_ERR_RA_NOT_AUTHORIZED, NULL,
                             _("Authentication error from server: %s"), arg);
  else if (strcmp(status, "success") != 0 || arg)
    return svn_error_create(SVN_ERR_RA_NOT_AUTHORIZED, NULL,
                            _("Unexpected server response to authentication"));
  return SVN_NO_ERROR;
}