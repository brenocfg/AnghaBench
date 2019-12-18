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
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  combine_forked_mergeinfo_props (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_mergeinfo_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_to_string (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_string_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
apply_single_mergeinfo_prop_change(const svn_string_t **result_val,
                                   svn_boolean_t *conflict_remains,
                                   svn_boolean_t *did_merge,
                                   const svn_string_t *base_val,
                                   const svn_string_t *old_val,
                                   const svn_string_t *new_val,
                                   const svn_string_t *working_val,
                                   apr_pool_t *result_pool,
                                   apr_pool_t *scratch_pool)
{
  if ((working_val && ! base_val)
      || (! working_val && base_val)
      || (working_val && base_val
          && !svn_string_compare(working_val, base_val)))
    {
      /* Locally changed property */
      if (working_val)
        {
          if (svn_string_compare(working_val, new_val))
            /* The new value equals the changed value: a no-op merge */
            *did_merge = TRUE;
          else
            {
              /* We have base, WC, and new values.  Discover
                 deltas between base <-> WC, and base <->
                 incoming.  Combine those deltas, and apply
                 them to base to get the new value. */
              SVN_ERR(combine_forked_mergeinfo_props(&new_val, old_val,
                                                     working_val,
                                                     new_val,
                                                     result_pool,
                                                     scratch_pool));
              *result_val = new_val;
              *did_merge = TRUE;
            }
        }
      else
        {
          /* There is a base_val but no working_val */
          *conflict_remains = TRUE;
        }
    }

  else if (! working_val) /* means !working_val && !base_val due
                             to conditions above: no prop at all */
    {
      /* Discover any mergeinfo additions in the
         incoming value relative to the base, and
         "combine" those with the empty WC value. */
      svn_mergeinfo_t deleted_mergeinfo, added_mergeinfo;
      svn_string_t *mergeinfo_string;

      SVN_ERR(diff_mergeinfo_props(&deleted_mergeinfo,
                                   &added_mergeinfo,
                                   old_val, new_val, scratch_pool));
      SVN_ERR(svn_mergeinfo_to_string(&mergeinfo_string,
                                      added_mergeinfo, result_pool));
      *result_val = mergeinfo_string;
    }

  else /* means working && base && svn_string_compare(working, base) */
    {
      if (svn_string_compare(old_val, base_val))
        *result_val = new_val;
      else
        {
          /* We have base, WC, and new values.  Discover
             deltas between base <-> WC, and base <->
             incoming.  Combine those deltas, and apply
             them to base to get the new value. */
          SVN_ERR(combine_forked_mergeinfo_props(&new_val, old_val,
                                                 working_val,
                                                 new_val, result_pool,
                                                 scratch_pool));
          *result_val = new_val;
          *did_merge = TRUE;
        }
    }

  return SVN_NO_ERROR;
}