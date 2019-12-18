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
struct prologue_value {scalar_t__ kind; scalar_t__ k; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 scalar_t__ pv_constant ; 
 int /*<<< orphan*/  pv_constant_last (struct prologue_value**,struct prologue_value**) ; 
 scalar_t__ pv_register ; 
 scalar_t__ pv_unknown ; 

__attribute__((used)) static void
pv_add (struct prologue_value *sum,
        struct prologue_value *a,
        struct prologue_value *b)
{
  pv_constant_last (&a, &b);

  /* We can handle adding constants to registers, and other constants.  */
  if (b->kind == pv_constant
      && (a->kind == pv_register
          || a->kind == pv_constant))
    {
      sum->kind = a->kind;
      sum->reg = a->reg;    /* not meaningful if a is pv_constant, but
                               harmless */
      sum->k = a->k + b->k;
    }

  /* Anything else we don't know how to add.  We don't have a
     representation for, say, the sum of two registers, or a multiple
     of a register's value (adding a register to itself).  */
  else
    sum->kind = pv_unknown;
}