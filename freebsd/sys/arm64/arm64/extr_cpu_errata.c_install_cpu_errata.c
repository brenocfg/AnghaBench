#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {int midr_mask; int midr_value; int /*<<< orphan*/  (* quirk_install ) () ;} ;

/* Variables and functions */
 TYPE_1__* cpu_quirks ; 
 int get_midr () ; 
 size_t nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 () ; 

void
install_cpu_errata(void)
{
	u_int midr;
	size_t i;

	midr = get_midr();

	for (i = 0; i < nitems(cpu_quirks); i++) {
		if ((midr & cpu_quirks[i].midr_mask) ==
		    cpu_quirks[i].midr_value) {
			cpu_quirks[i].quirk_install();
		}
	}
}