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
struct aac_softc {int flags; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_intr; int /*<<< orphan*/  aac_irq; } ;

/* Variables and functions */
 int AAC_FLAGS_NEW_COMM ; 
 int EINVAL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/ * aac_filter ; 
 int /*<<< orphan*/ * aac_new_intr ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct aac_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aac_setup_intr(struct aac_softc *sc)
{

	if (sc->flags & AAC_FLAGS_NEW_COMM) {
		if (bus_setup_intr(sc->aac_dev, sc->aac_irq,
				   INTR_MPSAFE|INTR_TYPE_BIO, NULL,
				   aac_new_intr, sc, &sc->aac_intr)) {
			device_printf(sc->aac_dev, "can't set up interrupt\n");
			return (EINVAL);
		}
	} else {
		if (bus_setup_intr(sc->aac_dev, sc->aac_irq,
				   INTR_TYPE_BIO, aac_filter, NULL,
				   sc, &sc->aac_intr)) {
			device_printf(sc->aac_dev,
				      "can't set up interrupt filter\n");
			return (EINVAL);
		}
	}
	return (0);
}