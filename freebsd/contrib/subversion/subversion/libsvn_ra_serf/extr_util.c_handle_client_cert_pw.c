#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  auth_baton; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
struct TYPE_5__ {int /*<<< orphan*/  ssl_client_pw_auth_state; TYPE_1__* session; } ;
typedef  TYPE_2__ svn_ra_serf__connection_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {char* password; } ;
typedef  TYPE_3__ svn_auth_cred_ssl_client_cert_pw_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_AUTH_CRED_SSL_CLIENT_CERT_PW ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_auth_first_credentials (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth_next_credentials (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
handle_client_cert_pw(void *data,
                      const char *cert_path,
                      const char **password,
                      apr_pool_t *pool)
{
    svn_ra_serf__connection_t *conn = data;
    svn_ra_serf__session_t *session = conn->session;
    void *creds;

    *password = NULL;

    if (!conn->ssl_client_pw_auth_state)
      {
        SVN_ERR(svn_auth_first_credentials(&creds,
                                           &conn->ssl_client_pw_auth_state,
                                           SVN_AUTH_CRED_SSL_CLIENT_CERT_PW,
                                           cert_path,
                                           session->auth_baton,
                                           pool));
      }
    else
      {
        SVN_ERR(svn_auth_next_credentials(&creds,
                                          conn->ssl_client_pw_auth_state,
                                          pool));
      }

    if (creds)
      {
        svn_auth_cred_ssl_client_cert_pw_t *pw_creds;
        pw_creds = creds;
        *password = pw_creds->password;
      }

    return APR_SUCCESS;
}