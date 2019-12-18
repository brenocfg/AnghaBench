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
typedef  int /*<<< orphan*/  svn_auth_provider_object_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_auth__get_dummmy_simple_provider (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth__get_gpg_agent_simple_provider (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void
svn_auth_get_gpg_agent_simple_provider(svn_auth_provider_object_t **provider,
                                       apr_pool_t *pool)
{
#ifdef SVN_HAVE_GPG_AGENT
  svn_auth__get_gpg_agent_simple_provider(provider, pool);
#else
  svn_auth__get_dummmy_simple_provider(provider, pool);
#endif /* SVN_HAVE_GPG_AGENT */
}