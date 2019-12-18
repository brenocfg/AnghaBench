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
struct xenisrc {scalar_t__ xi_edgetrigger; int /*<<< orphan*/  xi_port; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int PIC_EOI ; 
 int /*<<< orphan*/  evtchn_mask_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_intr_pirq_eoi_source (struct intsrc*) ; 

__attribute__((used)) static void
xen_intr_pirq_disable_source(struct intsrc *base_isrc, int eoi)
{
	struct xenisrc *isrc;

	isrc = (struct xenisrc *)base_isrc;

	if (isrc->xi_edgetrigger == 0)
		evtchn_mask_port(isrc->xi_port);
	if (eoi == PIC_EOI)
		xen_intr_pirq_eoi_source(base_isrc);
}