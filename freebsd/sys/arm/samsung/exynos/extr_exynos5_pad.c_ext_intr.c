#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pad_softc {TYPE_1__* gpio_map; } ;
struct TYPE_4__ {int enabled; void (* ih ) (void*) ;void* ih_user; } ;
struct TYPE_3__ {int ngpio; scalar_t__ pend; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int READ4 (struct pad_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WRITE4 (struct pad_softc*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_2__* intr_map ; 

__attribute__((used)) static void
ext_intr(void *arg)
{
	struct pad_softc *sc;
	void (*ih) (void *);
	void *ih_user;
	int ngpio;
	int found;
	int reg;
	int i,j;
	int n,k;

	sc = arg;

	n = 0;
	for (i = 0; sc->gpio_map[i].ngpio != -1; i++) {
		found = 0;
		ngpio = sc->gpio_map[i].ngpio;

		if (sc->gpio_map[i].pend == 0) {
			n += ngpio;
			continue;
		}

		reg = READ4(sc, sc->gpio_map[i].port, sc->gpio_map[i].pend);

		for (j = 0; j < ngpio; j++) {
			if (reg & (1 << j)) {
				found = 1;

				k = (n + j);
				if (intr_map[k].enabled == 1) {
					ih = intr_map[k].ih;
					ih_user = intr_map[k].ih_user;
					ih(ih_user);
				}
			}
		}

		if (found) {
			/* ACK */
			WRITE4(sc, sc->gpio_map[i].port, sc->gpio_map[i].pend, reg);
		}

		n += ngpio;
	}
}