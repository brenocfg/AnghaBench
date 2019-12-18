#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  creds_cache; } ;
typedef  TYPE_1__ svn_auth_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_cache_key (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_auth_forget_credentials(svn_auth_baton_t *auth_baton,
                            const char *cred_kind,
                            const char *realmstring,
                            apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT((cred_kind && realmstring) || (!cred_kind && !realmstring));

  /* If we have a CRED_KIND and REALMSTRING, we clear out just the
     cached item (if any).  Otherwise, empty the whole hash. */
  if (cred_kind)
    {
      svn_hash_sets(auth_baton->creds_cache,
                    make_cache_key(cred_kind, realmstring, scratch_pool),
                    NULL);
    }
  else
    {
      apr_hash_clear(auth_baton->creds_cache);
    }

  return SVN_NO_ERROR;
}