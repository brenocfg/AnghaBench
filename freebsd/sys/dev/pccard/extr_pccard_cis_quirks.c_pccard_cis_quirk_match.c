#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ manufacturer; scalar_t__ product; scalar_t__* cis1_info; } ;
struct pccard_softc {TYPE_1__ card; } ;
struct pccard_cis_quirk {scalar_t__ manufacturer; scalar_t__ product; int /*<<< orphan*/ * cis1_info; } ;

/* Variables and functions */
 scalar_t__ PCMCIA_PRODUCT_INVALID ; 
 scalar_t__ PCMCIA_VENDOR_INVALID ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pccard_cis_quirk_match(struct pccard_softc *sc, struct pccard_cis_quirk *q)
{
	if ((sc->card.manufacturer == q->manufacturer) &&
		(sc->card.product == q->product) &&
		(((sc->card.manufacturer != PCMCIA_VENDOR_INVALID) &&
		  (sc->card.product != PCMCIA_PRODUCT_INVALID)) ||
		 ((sc->card.manufacturer == PCMCIA_VENDOR_INVALID) &&
		  (sc->card.product == PCMCIA_PRODUCT_INVALID) &&
		  sc->card.cis1_info[0] &&
		  (strcmp(sc->card.cis1_info[0], q->cis1_info[0]) == 0) &&
		  sc->card.cis1_info[1] &&
		  (strcmp(sc->card.cis1_info[1], q->cis1_info[1]) == 0))))
		return (1);
	return (0);
}