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
struct TYPE_3__ {int rlen; struct TYPE_3__** reps; scalar_t__ lv; } ;
typedef  TYPE_1__ mrb_irep ;
typedef  scalar_t__ mrb_bool ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static mrb_bool
lv_defined_p(mrb_irep *irep)
{
  int i;

  if (irep->lv) { return TRUE; }

  for (i = 0; i < irep->rlen; ++i) {
    if (lv_defined_p(irep->reps[i])) { return TRUE; }
  }

  return FALSE;
}