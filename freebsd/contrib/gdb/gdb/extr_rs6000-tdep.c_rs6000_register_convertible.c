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
struct reg {int fpr; } ;
struct TYPE_2__ {struct reg* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* gdbarch_tdep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rs6000_register_convertible (int n)
{
  const struct reg *reg = gdbarch_tdep (current_gdbarch)->regs + n;
  return reg->fpr;
}