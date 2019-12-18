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
struct gdbarch_tdep {int ppc_vr0_regnum; int ppc_vrsave_regnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 

int
altivec_register_p (int regno)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  if (tdep->ppc_vr0_regnum < 0 || tdep->ppc_vrsave_regnum < 0)
    return 0;
  else
    return (regno >= tdep->ppc_vr0_regnum && regno <= tdep->ppc_vrsave_regnum);
}