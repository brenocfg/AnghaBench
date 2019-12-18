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
typedef  int u32 ;
typedef  enum dbg_active_el { ____Placeholder_dbg_active_el } dbg_active_el ;

/* Variables and functions */
 int DBG_ACTIVE_EL1 ; 
 int DBG_MDSCR_KDE ; 
 int DBG_MDSCR_MDE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kde_ref_count ; 
 int /*<<< orphan*/  mde_ref_count ; 
 int mdscr_read () ; 
 int /*<<< orphan*/  mdscr_write (int) ; 
 int /*<<< orphan*/  preemptible () ; 
 scalar_t__ this_cpu_dec_return (int /*<<< orphan*/ ) ; 

void disable_debug_monitors(enum dbg_active_el el)
{
	u32 mdscr, disable = 0;

	WARN_ON(preemptible());

	if (this_cpu_dec_return(mde_ref_count) == 0)
		disable = ~DBG_MDSCR_MDE;

	if (el == DBG_ACTIVE_EL1 &&
	    this_cpu_dec_return(kde_ref_count) == 0)
		disable &= ~DBG_MDSCR_KDE;

	if (disable) {
		mdscr = mdscr_read();
		mdscr &= disable;
		mdscr_write(mdscr);
	}
}