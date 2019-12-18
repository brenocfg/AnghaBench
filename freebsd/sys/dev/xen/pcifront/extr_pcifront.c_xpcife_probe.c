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
struct pcifront_device {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_NOWILDCARD ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xpcife_probe(device_t dev)
{
#ifdef XEN_PCIDEV_FE_DEBUG
	struct pcifront_device *pdev = (struct pcifront_device *)device_get_ivars(dev);
	DPRINTF("xpcife probe (unit=%d)\n", pdev->unit);
#endif
	return (BUS_PROBE_NOWILDCARD);
}