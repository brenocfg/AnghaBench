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
struct prologue_value {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ pv_constant ; 

__attribute__((used)) static void
pv_constant_last (struct prologue_value **a,
                  struct prologue_value **b)
{
  if ((*a)->kind == pv_constant
      && (*b)->kind != pv_constant)
    {
      struct prologue_value *temp = *a;
      *a = *b;
      *b = temp;
    }
}