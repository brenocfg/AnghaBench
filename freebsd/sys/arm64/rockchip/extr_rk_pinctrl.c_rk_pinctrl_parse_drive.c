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
typedef  int /*<<< orphan*/  value ;
typedef  scalar_t__ uint32_t ;
struct rk_pinctrl_softc {TYPE_2__* conf; } ;
typedef  int /*<<< orphan*/  phandle_t ;
struct TYPE_4__ {int npin_drive; TYPE_1__* pin_drive; } ;
struct TYPE_3__ {scalar_t__ bank; scalar_t__ subbank; scalar_t__ ma; scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 

__attribute__((used)) static int
rk_pinctrl_parse_drive(struct rk_pinctrl_softc *sc, phandle_t node,
  uint32_t bank, uint32_t subbank, uint32_t *drive, uint32_t *offset)
{
	uint32_t value;
	int i;

	if (OF_getencprop(node, "drive-strength", &value,
	    sizeof(value)) != 0)
		return (-1);

	/* Map to the correct drive value */
	for (i = 0; i < sc->conf->npin_drive; i++) {
		if (sc->conf->pin_drive[i].bank != bank &&
		    sc->conf->pin_drive[i].subbank != subbank)
			continue;
		if (sc->conf->pin_drive[i].ma == value) {
			*drive = sc->conf->pin_drive[i].value;
			return (0);
		}
	}

	return (-1);
}