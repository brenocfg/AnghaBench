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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 unsigned int SVN_AUTH_SSL_CNMISMATCH ; 
 unsigned int SVN_AUTH_SSL_EXPIRED ; 
 unsigned int SVN_AUTH_SSL_NOTYETVALID ; 
 unsigned int SVN_AUTH_SSL_OTHER ; 
 unsigned int SVN_AUTH_SSL_UNKNOWNCA ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cstring_atoui (unsigned int*,char const*) ; 

__attribute__((used)) static svn_error_t *
show_cert_failures(const char *failure_string,
                   apr_pool_t *scratch_pool)
{
  unsigned int failures;

  SVN_ERR(svn_cstring_atoui(&failures, failure_string));

  if (0 == (failures & (SVN_AUTH_SSL_NOTYETVALID | SVN_AUTH_SSL_EXPIRED |
                        SVN_AUTH_SSL_CNMISMATCH | SVN_AUTH_SSL_UNKNOWNCA |
                        SVN_AUTH_SSL_OTHER)))
    return SVN_NO_ERROR;

  SVN_ERR(svn_cmdline_printf(
            scratch_pool, _("Automatic certificate validity check failed "
                            "because:\n")));

  if (failures & SVN_AUTH_SSL_NOTYETVALID)
    SVN_ERR(svn_cmdline_printf(
              scratch_pool, _("  The certificate is not yet valid.\n")));

  if (failures & SVN_AUTH_SSL_EXPIRED)
    SVN_ERR(svn_cmdline_printf(
              scratch_pool, _("  The certificate has expired.\n")));

  if (failures & SVN_AUTH_SSL_CNMISMATCH)
    SVN_ERR(svn_cmdline_printf(
              scratch_pool, _("  The certificate's Common Name (hostname) "
                              "does not match the remote hostname.\n")));

  if (failures & SVN_AUTH_SSL_UNKNOWNCA)
    SVN_ERR(svn_cmdline_printf(
              scratch_pool, _("  The certificate issuer is unknown.\n")));

  if (failures & SVN_AUTH_SSL_OTHER)
    SVN_ERR(svn_cmdline_printf(
              scratch_pool, _("  Unknown verification failure.\n")));

  return SVN_NO_ERROR;
}