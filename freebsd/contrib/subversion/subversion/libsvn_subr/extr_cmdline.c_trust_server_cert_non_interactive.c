#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  svn_auth_ssl_server_cert_info_t ;
struct TYPE_4__ {int accepted_failures; int /*<<< orphan*/  may_save; } ;
typedef  TYPE_1__ svn_auth_cred_ssl_server_trust_t ;
struct trust_server_cert_non_interactive_baton {scalar_t__ trust_server_cert_other_failure; scalar_t__ trust_server_cert_not_yet_valid; scalar_t__ trust_server_cert_expired; scalar_t__ trust_server_cert_cn_mismatch; scalar_t__ trust_server_cert_unknown_ca; } ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SVN_AUTH_SSL_CNMISMATCH ; 
 int SVN_AUTH_SSL_EXPIRED ; 
 int SVN_AUTH_SSL_NOTYETVALID ; 
 int SVN_AUTH_SSL_OTHER ; 
 int SVN_AUTH_SSL_UNKNOWNCA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
trust_server_cert_non_interactive(svn_auth_cred_ssl_server_trust_t **cred_p,
                                  void *baton,
                                  const char *realm,
                                  apr_uint32_t failures,
                                  const svn_auth_ssl_server_cert_info_t
                                    *cert_info,
                                  svn_boolean_t may_save,
                                  apr_pool_t *pool)
{
  struct trust_server_cert_non_interactive_baton *b = baton;
  apr_uint32_t non_ignored_failures;
  *cred_p = NULL;

  /* Mask away bits we are instructed to ignore. */
  non_ignored_failures = failures & ~(
        (b->trust_server_cert_unknown_ca ? SVN_AUTH_SSL_UNKNOWNCA : 0)
      | (b->trust_server_cert_cn_mismatch ? SVN_AUTH_SSL_CNMISMATCH : 0)
      | (b->trust_server_cert_expired ? SVN_AUTH_SSL_EXPIRED : 0)
      | (b->trust_server_cert_not_yet_valid ? SVN_AUTH_SSL_NOTYETVALID : 0)
      | (b->trust_server_cert_other_failure ? SVN_AUTH_SSL_OTHER : 0)
  );

  /* If no failures remain, accept the certificate. */
  if (non_ignored_failures == 0)
    {
      *cred_p = apr_pcalloc(pool, sizeof(**cred_p));
      (*cred_p)->may_save = FALSE;
      (*cred_p)->accepted_failures = failures;
    }

  return SVN_NO_ERROR;
}