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
struct prologue_value {int kind; int /*<<< orphan*/  k; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
#define  pv_constant 130 
#define  pv_register 129 
#define  pv_unknown 128 

__attribute__((used)) static int
pv_is_identical (struct prologue_value *a,
                 struct prologue_value *b)
{
  if (a->kind != b->kind)
    return 0;

  switch (a->kind)
    {
    case pv_unknown:
      return 1;
    case pv_constant:
      return (a->k == b->k);
    case pv_register:
      return (a->reg == b->reg && a->k == b->k);
    default:
      gdb_assert (0);
    }
}