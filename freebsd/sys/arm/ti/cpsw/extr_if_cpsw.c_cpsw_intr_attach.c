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
struct cpsw_softc {int /*<<< orphan*/ * ih_cookie; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb; } ;

/* Variables and functions */
 int CPSW_INTR_COUNT ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cpsw_softc*,int /*<<< orphan*/ *) ; 
 TYPE_1__* cpsw_intr_cb ; 

__attribute__((used)) static int
cpsw_intr_attach(struct cpsw_softc *sc)
{
	int i;

	for (i = 0; i < CPSW_INTR_COUNT; i++) {
		if (bus_setup_intr(sc->dev, sc->irq_res[i],
		    INTR_TYPE_NET | INTR_MPSAFE, NULL,
		    cpsw_intr_cb[i].cb, sc, &sc->ih_cookie[i]) != 0) {
			return (-1);
		}
	}

	return (0);
}