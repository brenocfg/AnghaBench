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

/* Variables and functions */
 int xen_release_msi (int) ; 

int
xen_msi_release(int *irqs, int count)
{
	int i, ret;

	for (i = 0; i < count; i++) {
		ret = xen_release_msi(irqs[i]);
		if (ret != 0)
			return (ret);
	}

	return (0);
}