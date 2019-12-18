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
struct gdbarch_tdep {int dummy; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  floatformat_ieee_double_big ; 
 int /*<<< orphan*/  frame_unwind_append_sniffer (struct gdbarch*,int /*<<< orphan*/ ) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  nbsd_ilp32_solib_svr4_fetch_link_map_offsets ; 
 int /*<<< orphan*/  set_gdbarch_long_double_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_long_double_format (struct gdbarch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_solib_svr4_fetch_link_map_offsets (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc32obsd_pc_in_sigtramp ; 
 int /*<<< orphan*/  sparc32obsd_sigtramp_frame_sniffer ; 

__attribute__((used)) static void
sparc32obsd_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* OpenBSD doesn't support the 128-bit `long double' from the psABI.  */
  set_gdbarch_long_double_bit (gdbarch, 64);
  set_gdbarch_long_double_format (gdbarch, &floatformat_ieee_double_big);

  set_gdbarch_pc_in_sigtramp (gdbarch, sparc32obsd_pc_in_sigtramp);
  frame_unwind_append_sniffer (gdbarch, sparc32obsd_sigtramp_frame_sniffer);

  set_solib_svr4_fetch_link_map_offsets
    (gdbarch, nbsd_ilp32_solib_svr4_fetch_link_map_offsets);
}