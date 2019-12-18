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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_string_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
apply_single_prop_delete(const svn_string_t **result_val,
                         svn_boolean_t *conflict_remains,
                         svn_boolean_t *did_merge,
                         const svn_string_t *base_val,
                         const svn_string_t *old_val,
                         const svn_string_t *working_val)
{
  *conflict_remains = FALSE;

  if (! base_val)
    {
      if (working_val
          && !svn_string_compare(working_val, old_val))
        {
          /* We are trying to delete a locally-added prop. */
          *conflict_remains = TRUE;
        }
      else
        {
          *result_val = NULL;
          if (old_val)
            /* This is a merge, merging a delete into non-existent
               property or a local addition of same prop value. */
            *did_merge = TRUE;
        }
    }

  else if (svn_string_compare(base_val, old_val))
    {
       if (working_val)
         {
           if (svn_string_compare(working_val, old_val))
             /* they have the same values, so it's an update */
             *result_val = NULL;
           else
             *conflict_remains = TRUE;
         }
       else
         /* The property is locally deleted from the same value, so it's
            a merge */
         *did_merge = TRUE;
    }

  else
    *conflict_remains = TRUE;

  return SVN_NO_ERROR;
}