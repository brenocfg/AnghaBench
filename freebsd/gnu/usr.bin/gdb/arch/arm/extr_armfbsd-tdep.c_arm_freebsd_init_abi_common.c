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
struct gdbarch_tdep {int lowest_pc; int /*<<< orphan*/  jb_elt_size; int /*<<< orphan*/  jb_pc; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_FBSD_JB_ELEMENT_SIZE ; 
 int /*<<< orphan*/  ARM_FBSD_JB_PC ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 

__attribute__((used)) static void
arm_freebsd_init_abi_common (struct gdbarch_info info,
			    struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  tdep->lowest_pc = 0x8000;

  tdep->jb_pc = ARM_FBSD_JB_PC;
  tdep->jb_elt_size = ARM_FBSD_JB_ELEMENT_SIZE;
}