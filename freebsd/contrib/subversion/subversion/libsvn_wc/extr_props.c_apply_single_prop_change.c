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
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apply_single_generic_prop_change (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* apply_single_mergeinfo_prop_change (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
apply_single_prop_change(const svn_string_t **result_val,
                         svn_boolean_t *conflict_remains,
                         svn_boolean_t *did_merge,
                         const char *propname,
                         const svn_string_t *base_val,
                         const svn_string_t *old_val,
                         const svn_string_t *new_val,
                         const svn_string_t *working_val,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  svn_boolean_t merged_prop = FALSE;

  *conflict_remains = FALSE;

  /* Note: The purpose is to apply the change (old_val -> new_val) onto
     (working_val). There is no need for base_val to be involved in the
     process except as a bit of context to help the user understand and
     resolve any conflict. */

  /* Decide how to merge, based on whether we know anything special about
     the property. */
  if (strcmp(propname, SVN_PROP_MERGEINFO) == 0)
    {
      /* We know how to merge any mergeinfo property change...

         ...But Issue #3896 'mergeinfo syntax errors should be treated
         gracefully' might thwart us.  If bogus mergeinfo is present we
         can't merge intelligently, so let the standard method deal with
         it instead. */
      svn_error_t *err = apply_single_mergeinfo_prop_change(result_val,
                                                            conflict_remains,
                                                            did_merge,
                                                            base_val,
                                                            old_val,
                                                            new_val,
                                                            working_val,
                                                            result_pool,
                                                            scratch_pool);
       if (err)
         {
           if (err->apr_err == SVN_ERR_MERGEINFO_PARSE_ERROR)
             svn_error_clear(err);
           else
             return svn_error_trace(err);
           }
       else
         {
           merged_prop = TRUE;
         }
    }

  if (!merged_prop)
    {
      /* The standard method: perform a simple update automatically, but
         pass any other kind of merge to maybe_generate_propconflict(). */

      SVN_ERR(apply_single_generic_prop_change(result_val, conflict_remains,
                                               did_merge,
                                               old_val, new_val, working_val));
    }

  return SVN_NO_ERROR;
}