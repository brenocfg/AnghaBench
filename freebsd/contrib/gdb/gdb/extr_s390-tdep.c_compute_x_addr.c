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
struct prologue_value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pv_add (struct prologue_value*,struct prologue_value*,struct prologue_value*) ; 
 int /*<<< orphan*/  pv_set_to_constant (struct prologue_value*,int) ; 

__attribute__((used)) static void
compute_x_addr (struct prologue_value *addr, 
                struct prologue_value *gpr,
                int d2, unsigned int x2, unsigned int b2)
{
  /* We can't just add stuff directly in addr; it might alias some of
     the registers we need to read.  */
  struct prologue_value result;

  pv_set_to_constant (&result, d2);
  if (x2)
    pv_add (&result, &result, &gpr[x2]);
  if (b2)
    pv_add (&result, &result, &gpr[b2]);

  *addr = result;
}