#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  va_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  V_ADP_INITIALIZED ; 
 int /*<<< orphan*/  V_ADP_REGISTERED ; 
 TYPE_1__* biosadapter ; 
 int biosadapters ; 
 int /*<<< orphan*/  config_done (TYPE_1__*) ; 
 int /*<<< orphan*/  probe_adapters () ; 
 int /*<<< orphan*/  probe_done (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  vga_sub_configure (int) ; 
 scalar_t__ vid_register (TYPE_1__*) ; 

__attribute__((used)) static int
vga_configure(int flags)
{
    int i;

    probe_adapters();
    for (i = 0; i < biosadapters; ++i) {
	if (!probe_done(&biosadapter[i]))
	    continue;
	biosadapter[i].va_flags |= V_ADP_INITIALIZED;
	if (!config_done(&biosadapter[i])) {
	    if (vid_register(&biosadapter[i]) < 0)
		continue;
	    biosadapter[i].va_flags |= V_ADP_REGISTERED;
	}
    }
    if (vga_sub_configure != NULL)
	(*vga_sub_configure)(flags);

    return biosadapters;
}