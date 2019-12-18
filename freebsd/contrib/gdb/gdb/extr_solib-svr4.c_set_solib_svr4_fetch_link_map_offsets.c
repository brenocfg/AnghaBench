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
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fetch_link_map_offsets_gdbarch_data ; 
 int /*<<< orphan*/  set_gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ,struct link_map_offsets* (*) ()) ; 

void
set_solib_svr4_fetch_link_map_offsets (struct gdbarch *gdbarch,
                                       struct link_map_offsets *(*flmo) (void))
{
  set_gdbarch_data (gdbarch, fetch_link_map_offsets_gdbarch_data, flmo);
}