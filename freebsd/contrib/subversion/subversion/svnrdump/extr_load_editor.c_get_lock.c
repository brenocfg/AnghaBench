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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVNRDUMP_PROP_LOCK ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_ATOMIC_REVPROPS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  lock_retry_func ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_handle_warning2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_ra__get_operational_lock (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_has_capability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_lock(const svn_string_t **lock_string_p,
         svn_ra_session_t *session,
         svn_cancel_func_t cancel_func,
         void *cancel_baton,
         apr_pool_t *pool)
{
  svn_boolean_t be_atomic;

  SVN_ERR(svn_ra_has_capability(session, &be_atomic,
                                SVN_RA_CAPABILITY_ATOMIC_REVPROPS,
                                pool));
  if (! be_atomic)
    {
      /* Pre-1.7 servers can't lock without a race condition.  (Issue #3546) */
      svn_error_t *err =
        svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                         _("Target server does not support atomic revision "
                           "property edits; consider upgrading it to 1.7."));
      svn_handle_warning2(stderr, err, "svnrdump: ");
      svn_error_clear(err);
    }

  return svn_ra__get_operational_lock(lock_string_p, NULL, session,
                                      SVNRDUMP_PROP_LOCK, FALSE,
                                      10 /* retries */, lock_retry_func, NULL,
                                      cancel_func, cancel_baton, pool);
}