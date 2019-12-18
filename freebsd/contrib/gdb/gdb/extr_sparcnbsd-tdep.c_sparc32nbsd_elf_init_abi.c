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
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nbsd_ilp32_solib_svr4_fetch_link_map_offsets ; 
 int /*<<< orphan*/  set_solib_svr4_fetch_link_map_offsets (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc32nbsd_init_abi (struct gdbarch_info,struct gdbarch*) ; 

__attribute__((used)) static void
sparc32nbsd_elf_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  sparc32nbsd_init_abi (info, gdbarch);

  set_solib_svr4_fetch_link_map_offsets
    (gdbarch, nbsd_ilp32_solib_svr4_fetch_link_map_offsets);
}