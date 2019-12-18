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
typedef  int vmem_addr_t ;
struct fsl_pcib_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int M_BESTFIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  VMEM_ADDR_MAX ; 
 int /*<<< orphan*/  VMEM_ADDR_MIN ; 
 struct fsl_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msi_vmem ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 int vmem_xalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int fsl_pcib_alloc_msi(device_t dev, device_t child,
    int count, int maxcount, int *irqs)
{
	struct fsl_pcib_softc *sc;
	vmem_addr_t start;
	int err, i;

	sc = device_get_softc(dev);
	if (msi_vmem == NULL)
		return (ENODEV);

	err = vmem_xalloc(msi_vmem, count, powerof2(count), 0, 0,
	    VMEM_ADDR_MIN, VMEM_ADDR_MAX, M_BESTFIT | M_WAITOK, &start);

	if (err)
		return (err);

	for (i = 0; i < count; i++)
		irqs[i] = start + i;

	return (0);
}