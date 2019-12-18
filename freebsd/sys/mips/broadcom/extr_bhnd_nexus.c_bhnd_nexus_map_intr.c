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
typedef  int /*<<< orphan*/  u_int ;
struct bcm_mips_intr_map_data {int /*<<< orphan*/  mdata; int /*<<< orphan*/  ivec; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 uintptr_t BHND_BUS_GET_INTR_DOMAIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTR_MAP_DATA_BCM_MIPS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int bhnd_get_intr_ivec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ intr_alloc_map_data (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  intr_map_irq (int /*<<< orphan*/ *,uintptr_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bhnd_nexus_map_intr(device_t dev, device_t child, u_int intr, rman_res_t *irq)
{
	struct bcm_mips_intr_map_data	*imd;
	u_int				 ivec;
	uintptr_t			 xref;
	int				 error;

	/* Fetch the backplane interrupt vector */
	if ((error = bhnd_get_intr_ivec(child, intr, &ivec))) {
		device_printf(dev, "error fetching ivec for intr %u: %d\n",
		    intr, error);
		return (error);
	}

	/* Determine our interrupt domain */
	xref = BHND_BUS_GET_INTR_DOMAIN(dev, child, false);
	KASSERT(xref != 0, ("missing interrupt domain"));

	/* Allocate our map data */
	imd = (struct bcm_mips_intr_map_data *)intr_alloc_map_data(
	    INTR_MAP_DATA_BCM_MIPS, sizeof(*imd), M_WAITOK | M_ZERO);
	imd->ivec = ivec;

	/* Map the IRQ */
	*irq = intr_map_irq(NULL, xref, &imd->mdata);
	return (0);
}