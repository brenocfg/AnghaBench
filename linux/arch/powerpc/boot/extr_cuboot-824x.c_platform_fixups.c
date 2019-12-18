#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int bi_busfreq; int /*<<< orphan*/  bi_intfreq; int /*<<< orphan*/  bi_enetaddr; int /*<<< orphan*/  bi_memsize; int /*<<< orphan*/  bi_memstart; } ;

/* Variables and functions */
 TYPE_1__ bd ; 
 int /*<<< orphan*/  dt_fixup_cpu_clocks (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dt_fixup_mac_addresses (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_fixup_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* find_node_by_devtype (void*,char*) ; 
 void* get_parent (void*) ; 
 int /*<<< orphan*/  setprop (void*,char*,int*,int) ; 

__attribute__((used)) static void platform_fixups(void)
{
	void *soc;

	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_mac_addresses(bd.bi_enetaddr);
	dt_fixup_cpu_clocks(bd.bi_intfreq, bd.bi_busfreq / 4, bd.bi_busfreq);

	soc = find_node_by_devtype(NULL, "soc");
	if (soc) {
		void *serial = NULL;

		setprop(soc, "bus-frequency", &bd.bi_busfreq,
		        sizeof(bd.bi_busfreq));

		while ((serial = find_node_by_devtype(serial, "serial"))) {
			if (get_parent(serial) != soc)
				continue;

			setprop(serial, "clock-frequency", &bd.bi_busfreq,
			        sizeof(bd.bi_busfreq));
		}
	}
}