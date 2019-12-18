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
 int ENODEV ; 
 int /*<<< orphan*/ * msi_vmem ; 
 int /*<<< orphan*/  vmem_xfree (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int fsl_pcib_release_msi(device_t dev, device_t child,
    int count, int *irqs)
{
	if (msi_vmem == NULL)
		return (ENODEV);

	vmem_xfree(msi_vmem, irqs[0], count);
	return (0);
}