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
struct xenisrc {int /*<<< orphan*/  xi_pirq; } ;
struct physdev_eoi {int /*<<< orphan*/  irq; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_eoi*) ; 
 int /*<<< orphan*/  PHYSDEVOP_eoi ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xen_intr_pirq_eoi_map ; 
 scalar_t__ xen_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xen_intr_pirq_eoi_source(struct intsrc *base_isrc)
{
	struct xenisrc *isrc;
	int error;

	isrc = (struct xenisrc *)base_isrc;

	if (xen_test_bit(isrc->xi_pirq, xen_intr_pirq_eoi_map)) {
		struct physdev_eoi eoi = { .irq = isrc->xi_pirq };

		error = HYPERVISOR_physdev_op(PHYSDEVOP_eoi, &eoi);
		if (error != 0)
			panic("Unable to EOI PIRQ#%d: %d\n",
			    isrc->xi_pirq, error);
	}
}