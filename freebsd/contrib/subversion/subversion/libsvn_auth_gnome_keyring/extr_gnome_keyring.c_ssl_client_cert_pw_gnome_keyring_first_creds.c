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
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH__GNOME_KEYRING_PASSWORD_TYPE ; 
 int /*<<< orphan*/  password_get_gnome_keyring ; 
 int /*<<< orphan*/ * svn_auth__ssl_client_cert_pw_cache_get (void**,void**,void*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
ssl_client_cert_pw_gnome_keyring_first_creds(void **credentials,
                                             void **iter_baton,
                                             void *provider_baton,
                                             apr_hash_t *parameters,
                                             const char *realmstring,
                                             apr_pool_t *pool)
{
  return svn_auth__ssl_client_cert_pw_cache_get(
             credentials, iter_baton, provider_baton, parameters, realmstring,
             password_get_gnome_keyring, SVN_AUTH__GNOME_KEYRING_PASSWORD_TYPE,
             pool);
}