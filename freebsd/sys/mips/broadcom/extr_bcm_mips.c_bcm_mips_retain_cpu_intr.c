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
typedef  size_t u_int ;
struct resource {int dummy; } ;
struct bcm_mips_softc {size_t num_cpuirqs; struct bcm_mips_cpuirq* cpuirqs; } ;
struct bcm_mips_irqsrc {int refs; struct bcm_mips_cpuirq* cpuirq; int /*<<< orphan*/  ivec; } ;
struct bcm_mips_cpuirq {scalar_t__ refs; int irq_rid; size_t mips_irq; struct bcm_mips_irqsrc* isrc_solo; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int bhnd_devclass_t ;

/* Variables and functions */
 size_t BCM_MIPS_IRQ_SHARED ; 
 int /*<<< orphan*/  BCM_MIPS_LOCK_ASSERT (struct bcm_mips_softc*,int /*<<< orphan*/ ) ; 
#define  BHND_DEVCLASS_CC 151 
#define  BHND_DEVCLASS_CC_B 150 
#define  BHND_DEVCLASS_CPU 149 
#define  BHND_DEVCLASS_ENET 148 
#define  BHND_DEVCLASS_ENET_MAC 147 
#define  BHND_DEVCLASS_ENET_PHY 146 
#define  BHND_DEVCLASS_EROM 145 
#define  BHND_DEVCLASS_INVALID 144 
#define  BHND_DEVCLASS_MEMC 143 
#define  BHND_DEVCLASS_NVRAM 142 
#define  BHND_DEVCLASS_OTHER 141 
#define  BHND_DEVCLASS_PCCARD 140 
#define  BHND_DEVCLASS_PCI 139 
#define  BHND_DEVCLASS_PCIE 138 
#define  BHND_DEVCLASS_PMU 137 
#define  BHND_DEVCLASS_RAM 136 
#define  BHND_DEVCLASS_SOC_BRIDGE 135 
#define  BHND_DEVCLASS_SOC_ROUTER 134 
#define  BHND_DEVCLASS_USB_DEV 133 
#define  BHND_DEVCLASS_USB_DUAL 132 
#define  BHND_DEVCLASS_USB_HOST 131 
#define  BHND_DEVCLASS_WLAN 130 
#define  BHND_DEVCLASS_WLAN_MAC 129 
#define  BHND_DEVCLASS_WLAN_PHY 128 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,size_t) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UINT_MAX ; 
 int /*<<< orphan*/ * bcm_mips_find_bhnd_parent (int /*<<< orphan*/ ) ; 
 int bhnd_get_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_device (struct resource*) ; 

__attribute__((used)) static int
bcm_mips_retain_cpu_intr(struct bcm_mips_softc *sc,
    struct bcm_mips_irqsrc *isrc, struct resource *res)
{
	struct bcm_mips_cpuirq	*cpuirq;
	bhnd_devclass_t		 devclass;
	device_t		 core;

	BCM_MIPS_LOCK_ASSERT(sc, MA_OWNED);

	/* Prefer existing assignment */
	if (isrc->cpuirq != NULL) {
		KASSERT(isrc->cpuirq->refs > 0, ("assigned IRQ has no "
		    "references"));

		/* Increment our reference count */
		if (isrc->refs == UINT_MAX)
			return (ENOMEM);	/* would overflow */

		isrc->refs++;
		return (0);
	}

	/* Use the device class of the bhnd core to which the interrupt
	 * vector is routed to determine whether a shared interrupt should
	 * be preferred. */
	devclass = BHND_DEVCLASS_OTHER;
	core = bcm_mips_find_bhnd_parent(rman_get_device(res));
	if (core != NULL)
		devclass = bhnd_get_class(core);

	switch (devclass) {
	case BHND_DEVCLASS_CC:
	case BHND_DEVCLASS_CC_B:
	case BHND_DEVCLASS_PMU:
	case BHND_DEVCLASS_RAM:
	case BHND_DEVCLASS_MEMC:
	case BHND_DEVCLASS_CPU:
	case BHND_DEVCLASS_SOC_ROUTER:
	case BHND_DEVCLASS_SOC_BRIDGE:
	case BHND_DEVCLASS_EROM:
	case BHND_DEVCLASS_NVRAM:
		/* Always use a shared interrupt for these devices */
		cpuirq = &sc->cpuirqs[BCM_MIPS_IRQ_SHARED];
		break;

	case BHND_DEVCLASS_PCI:
	case BHND_DEVCLASS_PCIE:
	case BHND_DEVCLASS_PCCARD:	
	case BHND_DEVCLASS_ENET:
	case BHND_DEVCLASS_ENET_MAC:
	case BHND_DEVCLASS_ENET_PHY:
	case BHND_DEVCLASS_WLAN:
	case BHND_DEVCLASS_WLAN_MAC:
	case BHND_DEVCLASS_WLAN_PHY:
	case BHND_DEVCLASS_USB_HOST:
	case BHND_DEVCLASS_USB_DEV:
	case BHND_DEVCLASS_USB_DUAL:
	case BHND_DEVCLASS_OTHER:
	case BHND_DEVCLASS_INVALID:
	default:
		/* Fall back on a shared interrupt */
		cpuirq = &sc->cpuirqs[BCM_MIPS_IRQ_SHARED];

		/* Try to assign a dedicated MIPS HW interrupt */
		for (u_int i = 0; i < sc->num_cpuirqs; i++) {
			if (i == BCM_MIPS_IRQ_SHARED)
				continue;

			if (sc->cpuirqs[i].irq_rid == -1)
				continue; /* unavailable */

			if (sc->cpuirqs[i].refs != 0)
				continue; /* already assigned */

			/* Found an unused CPU IRQ */
			cpuirq = &sc->cpuirqs[i];
			break;
		}

		break;
	}

	DPRINTF("routing backplane interrupt vector %u to MIPS IRQ %u\n",
	    isrc->ivec, cpuirq->mips_irq);

	KASSERT(isrc->cpuirq == NULL, ("CPU IRQ already assigned"));
	KASSERT(isrc->refs == 0, ("isrc has active references with no "
	    "assigned CPU IRQ"));
	KASSERT(cpuirq->refs == 1 || cpuirq->isrc_solo == NULL,
	    ("single isrc dispatch enabled on cpuirq with multiple refs"));

	/* Verify that bumping the cpuirq refcount below will not overflow */
	if (cpuirq->refs == UINT_MAX)
		return (ENOMEM);

	/* Increment cpuirq refcount on behalf of the isrc */
	cpuirq->refs++;

	/* Increment isrc refcount on behalf of the caller */
	isrc->refs++;

	/* Assign the IRQ to the isrc */
	isrc->cpuirq = cpuirq;

	/* Can we enable the single isrc dispatch path? */
	if (cpuirq->refs == 1 && cpuirq->mips_irq != BCM_MIPS_IRQ_SHARED)
		cpuirq->isrc_solo = isrc;

	return (0);
}