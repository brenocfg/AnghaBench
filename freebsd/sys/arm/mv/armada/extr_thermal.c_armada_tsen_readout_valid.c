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
typedef  int uint32_t ;
struct armada_thermal_softc {int /*<<< orphan*/  stat_res; TYPE_1__* tdata; } ;
typedef  int boolean_t ;
struct TYPE_2__ {int is_valid_shift; } ;
typedef  TYPE_1__ armada_tdata_t ;

/* Variables and functions */
 int TSEN_STAT_READOUT_VALID ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
armada_tsen_readout_valid(struct armada_thermal_softc *sc)
{
	const armada_tdata_t *tdata;
	uint32_t tsen_stat;
	boolean_t is_valid;

	tdata = sc->tdata;
	tsen_stat = bus_read_4(sc->stat_res, 0);

	tsen_stat >>= tdata->is_valid_shift;
	is_valid = ((tsen_stat & TSEN_STAT_READOUT_VALID) != 0);

	return (is_valid);
}