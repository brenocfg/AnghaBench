#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_OUT_OF_DATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_change_rev_prop2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_rev_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_compare (TYPE_1__ const*,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
check_and_set_revprop(svn_revnum_t *set_rev,
                      svn_ra_session_t *ra_session,
                      const char *propname,
                      const svn_string_t *original_propval,
                      const svn_string_t *propval,
                      apr_pool_t *pool)
{
  if (original_propval)
    {
      /* Ensure old value hasn't changed behind our back. */
      svn_string_t *current;
      SVN_ERR(svn_ra_rev_prop(ra_session, *set_rev, propname, &current, pool));

      if (original_propval->data && (! current))
        {
          return svn_error_createf(
                  SVN_ERR_RA_OUT_OF_DATE, NULL,
                  _("revprop '%s' in r%ld is unexpectedly absent "
                    "in repository (maybe someone else deleted it?)"),
                  propname, *set_rev);
        }
      else if (original_propval->data
               && (! svn_string_compare(original_propval, current)))
        {
          return svn_error_createf(
                  SVN_ERR_RA_OUT_OF_DATE, NULL,
                  _("revprop '%s' in r%ld has unexpected value "
                    "in repository (maybe someone else changed it?)"),
                  propname, *set_rev);
        }
      else if ((! original_propval->data) && current)
        {
          return svn_error_createf(
                  SVN_ERR_RA_OUT_OF_DATE, NULL,
                  _("revprop '%s' in r%ld is unexpectedly present "
                    "in repository (maybe someone else set it?)"),
                  propname, *set_rev);
        }
    }

  SVN_ERR(svn_ra_change_rev_prop2(ra_session, *set_rev, propname,
                                  NULL, propval, pool));

  return SVN_NO_ERROR;
}