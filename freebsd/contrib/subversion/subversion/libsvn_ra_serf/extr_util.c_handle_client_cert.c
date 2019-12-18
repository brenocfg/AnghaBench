#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  auth_baton; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
struct TYPE_6__ {int /*<<< orphan*/  ssl_client_auth_state; TYPE_1__* session; } ;
typedef  TYPE_2__ svn_ra_serf__connection_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {char* cert_file; } ;
typedef  TYPE_3__ svn_auth_cred_ssl_client_cert_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_CRED_SSL_CLIENT_CERT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* construct_realm (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_auth_first_credentials (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth_next_credentials (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
handle_client_cert(void *data,
                   const char **cert_path,
                   apr_pool_t *pool)
{
    svn_ra_serf__connection_t *conn = data;
    svn_ra_serf__session_t *session = conn->session;
    const char *realm;
    void *creds;

    *cert_path = NULL;

    realm = construct_realm(session, session->pool);

    if (!conn->ssl_client_auth_state)
      {
        SVN_ERR(svn_auth_first_credentials(&creds,
                                           &conn->ssl_client_auth_state,
                                           SVN_AUTH_CRED_SSL_CLIENT_CERT,
                                           realm,
                                           session->auth_baton,
                                           pool));
      }
    else
      {
        SVN_ERR(svn_auth_next_credentials(&creds,
                                          conn->ssl_client_auth_state,
                                          session->pool));
      }

    if (creds)
      {
        svn_auth_cred_ssl_client_cert_t *client_creds;
        client_creds = creds;
        *cert_path = client_creds->cert_file;
      }

    return SVN_NO_ERROR;
}