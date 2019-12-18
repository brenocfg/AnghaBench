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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int xen_msi_alloc (int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static int
nexus_xen_alloc_msi(device_t pcib, device_t dev, int count, int maxcount, int *irqs)
{

	return (xen_msi_alloc(dev, count, maxcount, irqs));
}