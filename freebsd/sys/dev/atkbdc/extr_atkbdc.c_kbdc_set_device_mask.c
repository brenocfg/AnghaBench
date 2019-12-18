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
struct TYPE_2__ {int command_mask; int quirks; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int KBDC_QUIRK_KEEP_ACTIVATED ; 
 int KBD_AUX_CONTROL_BITS ; 
 int KBD_KBD_CONTROL_BITS ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 

void
kbdc_set_device_mask(KBDC p, int mask)
{
    kbdcp(p)->command_mask = 
	mask & (((kbdcp(p)->quirks & KBDC_QUIRK_KEEP_ACTIVATED)
	    ? 0 : KBD_KBD_CONTROL_BITS) | KBD_AUX_CONTROL_BITS);
}