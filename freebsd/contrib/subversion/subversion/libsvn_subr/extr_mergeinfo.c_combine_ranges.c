#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ start; scalar_t__ end; scalar_t__ inheritable; } ;
typedef  TYPE_1__ svn_merge_range_t ;
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static svn_boolean_t
combine_ranges(svn_merge_range_t *output,
               const svn_merge_range_t *in1,
               const svn_merge_range_t *in2,
               svn_boolean_t consider_inheritance)
{
  if (in1->start <= in2->end && in2->start <= in1->end)
    {
      if (!consider_inheritance
          || (consider_inheritance
              && (in1->inheritable == in2->inheritable)))
        {
          output->start = MIN(in1->start, in2->start);
          output->end = MAX(in1->end, in2->end);
          output->inheritable = (in1->inheritable || in2->inheritable);
          return TRUE;
        }
    }
  return FALSE;
}