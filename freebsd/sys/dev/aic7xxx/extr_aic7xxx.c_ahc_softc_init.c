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
struct ahc_softc {int chip; int unpause; int pause; int /*<<< orphan*/ * scb_data; } ;

/* Variables and functions */
 int AHC_PCI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCNTRL ; 
 int IRQMS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PAUSE ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
ahc_softc_init(struct ahc_softc *ahc)
{

	/* The IRQMS bit is only valid on VL and EISA chips */
	if ((ahc->chip & AHC_PCI) == 0)
		ahc->unpause = ahc_inb(ahc, HCNTRL) & IRQMS;
	else
		ahc->unpause = 0;
	ahc->pause = ahc->unpause | PAUSE; 
	/* XXX The shared scb data stuff should be deprecated */
	if (ahc->scb_data == NULL) {
		ahc->scb_data = malloc(sizeof(*ahc->scb_data),
				       M_DEVBUF, M_NOWAIT);
		if (ahc->scb_data == NULL)
			return (ENOMEM);
		memset(ahc->scb_data, 0, sizeof(*ahc->scb_data));
	}

	return (0);
}