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
typedef  int uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_NTB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 int* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntb_prefer_intx ; 
 int pci_remap_msix (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int
intel_ntb_remap_msix(device_t dev, uint32_t desired, uint32_t avail)
{
	u_int *vectors;
	uint32_t i;
	int rc;

	if (ntb_prefer_intx != 0)
		return (ENXIO);

	vectors = malloc(desired * sizeof(*vectors), M_NTB, M_ZERO | M_WAITOK);

	for (i = 0; i < desired; i++)
		vectors[i] = (i % avail) + 1;

	rc = pci_remap_msix(dev, desired, vectors);
	free(vectors, M_NTB);
	return (rc);
}