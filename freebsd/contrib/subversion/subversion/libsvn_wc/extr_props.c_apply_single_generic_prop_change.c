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
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_string_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
apply_single_generic_prop_change(const svn_string_t **result_val,
                                 svn_boolean_t *conflict_remains,
                                 svn_boolean_t *did_merge,
                                 const svn_string_t *old_val,
                                 const svn_string_t *new_val,
                                 const svn_string_t *working_val)
{
  SVN_ERR_ASSERT(old_val != NULL);

  /* If working_val is the same as new_val already then there is
   * nothing to do */
  if (working_val && new_val
      && svn_string_compare(working_val, new_val))
    {
      /* All values identical is a trivial, non-notifiable merge */
      if (! old_val || ! svn_string_compare(old_val, new_val))
        *did_merge = TRUE;
    }
  /* If working_val is the same as old_val... */
  else if (working_val && old_val
      && svn_string_compare(working_val, old_val))
    {
      /* A trivial update: change it to new_val. */
      *result_val = new_val;
    }
  else
    {
      /* Merge the change. */
      *conflict_remains = TRUE;
    }

  return SVN_NO_ERROR;
}