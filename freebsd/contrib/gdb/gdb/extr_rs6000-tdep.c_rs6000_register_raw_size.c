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
struct reg {int dummy; } ;
struct gdbarch_tdep {int /*<<< orphan*/  wordsize; struct reg* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int regsize (struct reg const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rs6000_register_raw_size (int n)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  const struct reg *reg = tdep->regs + n;
  return regsize (reg, tdep->wordsize);
}