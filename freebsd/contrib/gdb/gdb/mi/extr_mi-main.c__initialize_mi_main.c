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

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_GDBARCH_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deprecated_register_gdbarch_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_setup_architecture_data ; 
 int /*<<< orphan*/  old_regs ; 

void
_initialize_mi_main (void)
{
  DEPRECATED_REGISTER_GDBARCH_SWAP (old_regs);
  deprecated_register_gdbarch_swap (NULL, 0, mi_setup_architecture_data);
}