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
struct prologue_value {scalar_t__ kind; int reg; scalar_t__ k; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ pv_register ; 

__attribute__((used)) static int
pv_is_register (struct prologue_value *a, int r, CORE_ADDR k)
{
  return (a->kind == pv_register
          && a->reg == r
          && a->k == k);
}