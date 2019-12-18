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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct bcma_intr {int dummy; } ;
struct bcma_devinfo {scalar_t__ num_intrs; int /*<<< orphan*/  intrs; int /*<<< orphan*/ * res_agent; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BCMA_DINFO_COREIDX (struct bcma_devinfo*) ; 
 int /*<<< orphan*/  BCMA_DMP_CFG_OOB ; 
 int /*<<< orphan*/  BCMA_DMP_CONFIG ; 
 int /*<<< orphan*/  BCMA_DMP_GET_FLAG (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCMA_DMP_OOBSELOUT (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ BCMA_DMP_OOBSEL_BUSLINE_MASK ; 
 scalar_t__ BCMA_DMP_OOBSEL_SHIFT (scalar_t__) ; 
 int /*<<< orphan*/  BCMA_DMP_OOB_OUTWIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCMA_OOB_BANK_INTR ; 
 scalar_t__ BCMA_OOB_NUM_SEL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct bcma_intr*,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT_MAX ; 
 struct bcma_intr* bcma_alloc_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ bhnd_bus_read_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  i_link ; 

__attribute__((used)) static int
bcma_dinfo_init_intrs(device_t bus, device_t child,
    struct bcma_devinfo *dinfo)
{
	uint32_t dmpcfg, oobw;

	/* Agent block must be mapped */
	if (dinfo->res_agent == NULL)
		return (0);

	/* Agent must support OOB */
	dmpcfg = bhnd_bus_read_4(dinfo->res_agent, BCMA_DMP_CONFIG);
	if (!BCMA_DMP_GET_FLAG(dmpcfg, BCMA_DMP_CFG_OOB))
		return (0);

	/* Fetch width of the OOB interrupt bank */
	oobw = bhnd_bus_read_4(dinfo->res_agent,
	     BCMA_DMP_OOB_OUTWIDTH(BCMA_OOB_BANK_INTR));
	if (oobw >= BCMA_OOB_NUM_SEL) {
		device_printf(bus, "ignoring invalid OOBOUTWIDTH for core %u: "
		    "%#x\n", BCMA_DINFO_COREIDX(dinfo), oobw);
		return (0);
	}

	/* Fetch OOBSEL busline values and populate list of interrupt
	 * descriptors */
	for (uint32_t sel = 0; sel < oobw; sel++) {
		struct bcma_intr	*intr;
		uint32_t		 selout;
		uint8_t			 line;

		if (dinfo->num_intrs == UINT_MAX)
			return (ENOMEM);
	
		selout = bhnd_bus_read_4(dinfo->res_agent, BCMA_DMP_OOBSELOUT(
		    BCMA_OOB_BANK_INTR, sel));

		line = (selout >> BCMA_DMP_OOBSEL_SHIFT(sel)) &
		    BCMA_DMP_OOBSEL_BUSLINE_MASK;

		intr = bcma_alloc_intr(BCMA_OOB_BANK_INTR, sel, line);
		if (intr == NULL) {
			device_printf(bus, "failed allocating interrupt "
			    "descriptor %#x for core %u\n", sel,
			    BCMA_DINFO_COREIDX(dinfo));
			return (ENOMEM);
		}

		STAILQ_INSERT_HEAD(&dinfo->intrs, intr, i_link);
		dinfo->num_intrs++;
	}

	return (0);
}