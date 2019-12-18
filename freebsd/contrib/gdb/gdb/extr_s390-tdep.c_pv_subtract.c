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
struct prologue_value {scalar_t__ kind; scalar_t__ reg; scalar_t__ k; } ;

/* Variables and functions */
 scalar_t__ pv_constant ; 
 int /*<<< orphan*/  pv_constant_last (struct prologue_value**,struct prologue_value**) ; 
 scalar_t__ pv_register ; 
 scalar_t__ pv_unknown ; 

__attribute__((used)) static void
pv_subtract (struct prologue_value *diff,
             struct prologue_value *a,
             struct prologue_value *b)
{
  pv_constant_last (&a, &b);

  /* We can subtract a constant from another constant, or from a
     register.  */
  if (b->kind == pv_constant
      && (a->kind == pv_register
          || a->kind == pv_constant))
    {
      diff->kind = a->kind;
      diff->reg = a->reg;    /* not always meaningful, but harmless */
      diff->k = a->k - b->k;
    }

  /* We can subtract a register from itself, yielding a constant.  */
  else if (a->kind == pv_register
           && b->kind == pv_register
           && a->reg == b->reg)
    {
      diff->kind = pv_constant;
      diff->k = a->k - b->k;
    }

  /* We don't know how to subtract anything else.  */
  else
    diff->kind = pv_unknown;
}