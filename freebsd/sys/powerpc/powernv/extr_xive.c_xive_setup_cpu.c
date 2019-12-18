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
struct xive_softc {int /*<<< orphan*/  sc_mem; } ;
struct TYPE_2__ {int /*<<< orphan*/  girq; } ;
struct xive_cpu {int cam; TYPE_1__ ipi_data; } ;

/* Variables and functions */
 struct xive_cpu* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int TM_QW2W2_VP ; 
 scalar_t__ TM_WORD0 ; 
 scalar_t__ TM_WORD2 ; 
 int /*<<< orphan*/  XIVE_TM_CPPR ; 
 scalar_t__ XIVE_TM_QW2_HV_POOL ; 
 int /*<<< orphan*/  XIVE_TM_SPC_PULL_POOL_CTX ; 
 int bus_read_4 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_read_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct xive_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_pic ; 
 int /*<<< orphan*/  xive_cpu_data ; 
 int /*<<< orphan*/  xive_unmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xive_write_1 (struct xive_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xive_setup_cpu(void)
{
	struct xive_softc *sc;
	struct xive_cpu *cpup;
	uint32_t val;

	cpup = DPCPU_PTR(xive_cpu_data);

	sc = device_get_softc(root_pic);

	val = bus_read_4(sc->sc_mem, XIVE_TM_QW2_HV_POOL + TM_WORD2);
	if (val & TM_QW2W2_VP)
		bus_read_8(sc->sc_mem, XIVE_TM_SPC_PULL_POOL_CTX);

	bus_write_4(sc->sc_mem, XIVE_TM_QW2_HV_POOL + TM_WORD0, 0xff);
	bus_write_4(sc->sc_mem, XIVE_TM_QW2_HV_POOL + TM_WORD2,
	    TM_QW2W2_VP | cpup->cam);

	xive_unmask(root_pic, cpup->ipi_data.girq, &cpup->ipi_data);
	xive_write_1(sc, XIVE_TM_CPPR, 0xff);
}