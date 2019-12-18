#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVNSYNC_PROP_LOCK ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_ATOMIC_REVPROPS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_cancel ; 
 int /*<<< orphan*/  lock_retry_func ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_handle_warning2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_ra__get_operational_lock (TYPE_1__ const**,TYPE_1__ const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_has_capability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_lock(const svn_string_t **lock_string_p,
         svn_ra_session_t *session,
         svn_boolean_t steal_lock,
         apr_pool_t *pool)
{
  svn_error_t *err;
  svn_boolean_t be_atomic;
  const svn_string_t *stolen_lock;

  SVN_ERR(svn_ra_has_capability(session, &be_atomic,
                                SVN_RA_CAPABILITY_ATOMIC_REVPROPS,
                                pool));
  if (! be_atomic)
    {
      /* Pre-1.7 server.  Can't lock without a race condition.
         See issue #3546.
       */
      err = svn_error_create(
              SVN_ERR_UNSUPPORTED_FEATURE, NULL,
              _("Target server does not support atomic revision property "
                "edits; consider upgrading it to 1.7 or using an external "
                "locking program"));
      svn_handle_warning2(stderr, err, "svnsync: ");
      svn_error_clear(err);
    }

  err = svn_ra__get_operational_lock(lock_string_p, &stolen_lock, session,
                                     SVNSYNC_PROP_LOCK, steal_lock,
                                     10 /* retries */, lock_retry_func, NULL,
                                     check_cancel, NULL, pool);
  if (!err && stolen_lock)
    {
      return svn_cmdline_printf(pool,
                                _("Stole lock previously held by '%s'\n"),
                                stolen_lock->data);
    }
  return err;
}