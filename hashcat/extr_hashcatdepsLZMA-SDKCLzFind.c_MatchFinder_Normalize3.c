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
typedef  scalar_t__ UInt32 ;
typedef  scalar_t__ CLzRef ;

/* Variables and functions */
 scalar_t__ kEmptyHashValue ; 

void MatchFinder_Normalize3(UInt32 subValue, CLzRef *items, size_t numItems)
{
  size_t i;
  for (i = 0; i < numItems; i++)
  {
    UInt32 value = items[i];
    if (value <= subValue)
      value = kEmptyHashValue;
    else
      value -= subValue;
    items[i] = value;
  }
}