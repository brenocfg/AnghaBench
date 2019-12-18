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
 scalar_t__ SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* combine_mergeinfo_props (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 scalar_t__ svn_string_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
apply_single_prop_add(const svn_string_t **result_val,
                      svn_boolean_t *conflict_remains,
                      svn_boolean_t *did_merge,
                      const char *propname,
                      const svn_string_t *pristine_val,
                      const svn_string_t *new_val,
                      const svn_string_t *working_val,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)

{
  *conflict_remains = FALSE;

  if (working_val)
    {
      /* the property already exists in actual_props... */

      if (svn_string_compare(working_val, new_val))
        /* The value we want is already there, so it's a merge. */
        *did_merge = TRUE;

      else
        {
          svn_boolean_t merged_prop = FALSE;

          /* The WC difference doesn't match the new value.
           We only merge mergeinfo;  other props conflict */
          if (strcmp(propname, SVN_PROP_MERGEINFO) == 0)
            {
              const svn_string_t *merged_val;
              svn_error_t *err = combine_mergeinfo_props(&merged_val,
                                                         working_val,
                                                         new_val,
                                                         result_pool,
                                                         scratch_pool);

              /* Issue #3896 'mergeinfo syntax errors should be treated
                 gracefully': If bogus mergeinfo is present we can't
                 merge intelligently, so raise a conflict instead. */
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
                  *result_val = merged_val;
                  *did_merge = TRUE;
                }
            }

          if (!merged_prop)
            *conflict_remains = TRUE;
        }
    }
  else if (pristine_val)
    *conflict_remains = TRUE;
  else  /* property doesn't yet exist in actual_props...  */
    /* so just set it */
    *result_val = new_val;

  return SVN_NO_ERROR;
}