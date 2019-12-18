#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ depth; scalar_t__ schedule; scalar_t__ absent; scalar_t__ deleted; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_depth_exclude ; 
 scalar_t__ svn_wc_schedule_add ; 
 scalar_t__ svn_wc_schedule_normal ; 

svn_error_t *
svn_wc__entry_is_hidden(svn_boolean_t *hidden, const svn_wc_entry_t *entry)
{
  /* In English, the condition is: "the entry is not present, and I haven't
     scheduled something over the top of it."  */
  if (entry->deleted
      || entry->absent
      || entry->depth == svn_depth_exclude)
    {
      /* These kinds of nodes cannot be marked for deletion (which also
         means no "replace" either).  */
      SVN_ERR_ASSERT(entry->schedule == svn_wc_schedule_add
                     || entry->schedule == svn_wc_schedule_normal);

      /* Hidden if something hasn't been added over it.

         ### is this even possible with absent or excluded nodes?  */
      *hidden = entry->schedule != svn_wc_schedule_add;
    }
  else
    *hidden = FALSE;

  return SVN_NO_ERROR;
}