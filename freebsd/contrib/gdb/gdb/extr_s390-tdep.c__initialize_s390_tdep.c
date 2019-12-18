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
 int /*<<< orphan*/  bfd_arch_s390 ; 
 int /*<<< orphan*/  register_gdbarch_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_gdbarch_init ; 

void
_initialize_s390_tdep (void)
{

  /* Hook us into the gdbarch mechanism.  */
  register_gdbarch_init (bfd_arch_s390, s390_gdbarch_init);
}