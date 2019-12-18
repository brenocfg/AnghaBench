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
struct xencons_priv {int /*<<< orphan*/  evtchn; int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PAT_WRITE_BACK ; 
 int /*<<< orphan*/  pmap_mapdev_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_get_console_evtchn () ; 
 int /*<<< orphan*/  xen_get_console_mfn () ; 

__attribute__((used)) static void
xencons_early_init_ring(struct xencons_priv *cons)
{
	cons->intf = pmap_mapdev_attr(ptoa(xen_get_console_mfn()), PAGE_SIZE,
	    PAT_WRITE_BACK);
	cons->evtchn = xen_get_console_evtchn();
}