#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_7__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/ * (* change_rev_prop ) (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const* const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_ATOMIC_REVPROPS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const* const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_has_capability (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *svn_ra_change_rev_prop2(svn_ra_session_t *session,
                                     svn_revnum_t rev,
                                     const char *name,
                                     const svn_string_t *const *old_value_p,
                                     const svn_string_t *value,
                                     apr_pool_t *pool)
{
  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(rev));

  /* If an old value was specified, make sure the server supports
   * specifying it. */
  if (old_value_p)
    {
      svn_boolean_t has_atomic_revprops;

      SVN_ERR(svn_ra_has_capability(session, &has_atomic_revprops,
                                    SVN_RA_CAPABILITY_ATOMIC_REVPROPS,
                                    pool));

      if (!has_atomic_revprops)
        /* API violation.  (Should be an ASSERT, but gstein talked me
         * out of it.) */
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("Specifying 'old_value_p' is not allowed when "
                                   "the '%s' capability is not advertised, and "
                                   "could indicate a bug in your client"),
                                   SVN_RA_CAPABILITY_ATOMIC_REVPROPS);
    }

  return session->vtable->change_rev_prop(session, rev, name,
                                          old_value_p, value, pool);
}