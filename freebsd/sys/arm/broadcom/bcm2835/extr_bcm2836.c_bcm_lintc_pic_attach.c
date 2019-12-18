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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct intr_pic {int dummy; } ;
struct bcm_lintc_softc {int /*<<< orphan*/  bls_dev; struct bcm_lintc_irqsrc* bls_isrcs; } ;
struct bcm_lintc_irqsrc {size_t bli_irq; int /*<<< orphan*/  bli_isrc; int /*<<< orphan*/  bli_value; void* bli_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_LINTC_GIRR_IRQ_CORE (int /*<<< orphan*/ ) ; 
#define  BCM_LINTC_GPU_IRQ 137 
#define  BCM_LINTC_MBOX0_IRQ 136 
#define  BCM_LINTC_MBOX1_IRQ 135 
#define  BCM_LINTC_MBOX2_IRQ 134 
#define  BCM_LINTC_MBOX3_IRQ 133 
 size_t BCM_LINTC_NIRQS ; 
#define  BCM_LINTC_PMU_IRQ 132 
 void* BCM_LINTC_TCR_IRQ_EN_TIMER (int) ; 
#define  BCM_LINTC_TIMER0_IRQ 131 
#define  BCM_LINTC_TIMER1_IRQ 130 
#define  BCM_LINTC_TIMER2_IRQ 129 
#define  BCM_LINTC_TIMER3_IRQ 128 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_ISRCF_IPI ; 
 int /*<<< orphan*/  INTR_ISRCF_PPI ; 
 intptr_t OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_lintc_intr ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int intr_pic_claim_root (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,struct bcm_lintc_softc*,int /*<<< orphan*/ ) ; 
 struct intr_pic* intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_lintc_pic_attach(struct bcm_lintc_softc *sc)
{
	struct bcm_lintc_irqsrc *bisrcs;
	struct intr_pic *pic;
	int error;
	u_int flags;
	uint32_t irq;
	const char *name;
	intptr_t xref;

	bisrcs = sc->bls_isrcs;
	name = device_get_nameunit(sc->bls_dev);
	for (irq = 0; irq < BCM_LINTC_NIRQS; irq++) {
		bisrcs[irq].bli_irq = irq;
		switch (irq) {
		case BCM_LINTC_TIMER0_IRQ:
			bisrcs[irq].bli_mask = BCM_LINTC_TCR_IRQ_EN_TIMER(0);
			flags = INTR_ISRCF_PPI;
			break;
		case BCM_LINTC_TIMER1_IRQ:
			bisrcs[irq].bli_mask = BCM_LINTC_TCR_IRQ_EN_TIMER(1);
			flags = INTR_ISRCF_PPI;
			break;
		case BCM_LINTC_TIMER2_IRQ:
			bisrcs[irq].bli_mask = BCM_LINTC_TCR_IRQ_EN_TIMER(2);
			flags = INTR_ISRCF_PPI;
			break;
		case BCM_LINTC_TIMER3_IRQ:
			bisrcs[irq].bli_mask = BCM_LINTC_TCR_IRQ_EN_TIMER(3);
			flags = INTR_ISRCF_PPI;
			break;
		case BCM_LINTC_MBOX0_IRQ:
		case BCM_LINTC_MBOX1_IRQ:
		case BCM_LINTC_MBOX2_IRQ:
		case BCM_LINTC_MBOX3_IRQ:
			bisrcs[irq].bli_value = 0;	/* not used */
			flags = INTR_ISRCF_IPI;
			break;
		case BCM_LINTC_GPU_IRQ:
			bisrcs[irq].bli_value = BCM_LINTC_GIRR_IRQ_CORE(0);
			flags = 0;
			break;
		case BCM_LINTC_PMU_IRQ:
			bisrcs[irq].bli_value = 0;	/* not used */
			flags = INTR_ISRCF_PPI;
			break;
		default:
			bisrcs[irq].bli_value = 0;	/* not used */
			flags = 0;
			break;
		}

		error = intr_isrc_register(&bisrcs[irq].bli_isrc, sc->bls_dev,
		    flags, "%s,%u", name, irq);
		if (error != 0)
			return (error);
	}

	xref = OF_xref_from_node(ofw_bus_get_node(sc->bls_dev));
	pic = intr_pic_register(sc->bls_dev, xref);
	if (pic == NULL)
		return (ENXIO);

	return (intr_pic_claim_root(sc->bls_dev, xref, bcm_lintc_intr, sc, 0));
}