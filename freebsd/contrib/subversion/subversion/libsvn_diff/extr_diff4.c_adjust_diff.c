#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ modified_start; scalar_t__ modified_length; scalar_t__ original_length; scalar_t__ type; struct TYPE_4__* next; } ;
typedef  TYPE_1__ svn_diff_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 scalar_t__ svn_diff__type_conflict ; 
 scalar_t__ svn_diff__type_diff_modified ; 

__attribute__((used)) static void
adjust_diff(svn_diff_t *diff, svn_diff_t *adjust)
{
  svn_diff_t *hunk;
  apr_off_t range_start;
  apr_off_t range_end;
  apr_off_t adjustment;

  for (; adjust; adjust = adjust->next)
    {
      range_start = adjust->modified_start;
      range_end = range_start + adjust->modified_length;
      adjustment = adjust->original_length - adjust->modified_length;

      /* No change in line count, so no modifications. [3, 7] */
      if (adjustment == 0)
        continue;

      for (hunk = diff; hunk; hunk = hunk->next)
        {
          /* Changes are in the range before this hunk.  Adjust the start
           * of the hunk. [1, 2]
           */
          if (hunk->modified_start >= range_end)
            {
              hunk->modified_start += adjustment;
              continue;
            }

          /* Changes are in the range beyond this hunk.  No adjustments
           * needed. [1, 2]
           */
          if (hunk->modified_start + hunk->modified_length <= range_start)
            continue;

          /* From here on changes are in the range of this hunk. */

          /* This is a context hunk.  Adjust the length. [4]
           */
          if (hunk->type == svn_diff__type_diff_modified)
            {
              hunk->modified_length += adjustment;
              continue;
            }

          /* Mark as conflicted. This happens in the reverse case when a line
           * is added in range and in the forward case when a line is deleted
           * in range. [5 (reverse), 6 (forward)]
           */
          if (adjustment < 0)
              hunk->type = svn_diff__type_conflict;

          /* Adjust the length of this hunk (reverse the change). [5, 6] */
          hunk->modified_length -= adjustment;
        }
    }
}