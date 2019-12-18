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
 int MCE_FLUSH_ERAT ; 
 int MCE_FLUSH_SLB ; 
 int MCE_FLUSH_TLB ; 
 int /*<<< orphan*/  flush_and_reload_slb () ; 
 int /*<<< orphan*/  flush_erat () ; 
 int /*<<< orphan*/  tlbiel_all () ; 

__attribute__((used)) static int mce_flush(int what)
{
#ifdef CONFIG_PPC_BOOK3S_64
	if (what == MCE_FLUSH_SLB) {
		flush_and_reload_slb();
		return 1;
	}
#endif
	if (what == MCE_FLUSH_ERAT) {
		flush_erat();
		return 1;
	}
	if (what == MCE_FLUSH_TLB) {
		tlbiel_all();
		return 1;
	}

	return 0;
}