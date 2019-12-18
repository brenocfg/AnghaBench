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
struct TYPE_3__ {scalar_t__ type; struct TYPE_3__* next; } ;
typedef  TYPE_1__ svn_diff_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_diff__type_conflict ; 

svn_boolean_t
svn_diff_contains_conflicts(svn_diff_t *diff)
{
  while (diff != NULL)
    {
      if (diff->type == svn_diff__type_conflict)
        {
          return TRUE;
        }

      diff = diff->next;
    }

  return FALSE;
}