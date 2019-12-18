#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ppc_gp0_regnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* gdbarch_tdep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
e500_dwarf2_reg_to_regnum (int num)
{
  int regnum;
  if (0 <= num && num <= 31)
    return num + gdbarch_tdep (current_gdbarch)->ppc_gp0_regnum;
  else 
    return num;
}