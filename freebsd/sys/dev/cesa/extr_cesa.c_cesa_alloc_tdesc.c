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
struct cesa_tdma_desc {int dummy; } ;
struct cesa_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_GENERIC_ALLOC_LOCKED (struct cesa_softc*,struct cesa_tdma_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tdesc ; 

__attribute__((used)) static struct cesa_tdma_desc *
cesa_alloc_tdesc(struct cesa_softc *sc)
{
	struct cesa_tdma_desc *ctd;

	CESA_GENERIC_ALLOC_LOCKED(sc, ctd, tdesc);

	if (!ctd)
		device_printf(sc->sc_dev, "TDMA descriptors pool exhaused. "
		    "Consider increasing CESA_TDMA_DESCRIPTORS.\n");

	return (ctd);
}