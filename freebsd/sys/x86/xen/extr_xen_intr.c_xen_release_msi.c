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
struct physdev_unmap_pirq {int /*<<< orphan*/  pirq; } ;

/* Variables and functions */
 int ENXIO ; 
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_unmap_pirq*) ; 
 int /*<<< orphan*/  PHYSDEVOP_unmap_pirq ; 
 scalar_t__ intr_lookup_source (int) ; 
 int /*<<< orphan*/  xen_intr_release_isrc (struct xenisrc*) ; 

int
xen_release_msi(int vector)
{
	struct physdev_unmap_pirq unmap;
	struct xenisrc *isrc;
	int ret;

	isrc = (struct xenisrc *)intr_lookup_source(vector);
	if (isrc == NULL)
		return (ENXIO);

	unmap.pirq = isrc->xi_pirq;
	ret = HYPERVISOR_physdev_op(PHYSDEVOP_unmap_pirq, &unmap);
	if (ret != 0)
		return (ret);

	xen_intr_release_isrc(isrc);

	return (0);
}