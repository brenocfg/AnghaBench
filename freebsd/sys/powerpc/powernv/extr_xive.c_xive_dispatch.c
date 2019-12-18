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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct xive_softc {int dummy; } ;
struct xive_cpu {int /*<<< orphan*/  queue; } ;
struct trapframe {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct xive_cpu* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_XIVE_IRQS ; 
 int TM_QW3NSR_HE_SHIFT ; 
#define  TM_QW3_NSR_HE_LSI 131 
#define  TM_QW3_NSR_HE_NONE 130 
#define  TM_QW3_NSR_HE_PHYS 129 
#define  TM_QW3_NSR_HE_POOL 128 
 int /*<<< orphan*/  XIVE_TM_CPPR ; 
 int /*<<< orphan*/  XIVE_TM_SPC_ACK ; 
 struct xive_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  powerpc_dispatch_intr (scalar_t__,struct trapframe*) ; 
 int /*<<< orphan*/  xive_cpu_data ; 
 scalar_t__ xive_ipi_vector ; 
 int xive_read_2 (struct xive_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ xive_read_eq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xive_write_1 (struct xive_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xive_dispatch(device_t dev, struct trapframe *tf)
{
	struct xive_softc *sc;
	struct xive_cpu *xive_cpud;
	uint32_t vector;
	uint16_t ack;
	uint8_t cppr, he;

	sc = device_get_softc(dev);

	for (;;) {
		ack = xive_read_2(sc, XIVE_TM_SPC_ACK);
		cppr = (ack & 0xff);

		he = ack >> TM_QW3NSR_HE_SHIFT;

		if (he == TM_QW3_NSR_HE_NONE)
			break;
		switch (he) {
		case TM_QW3_NSR_HE_NONE:
			goto end;
		case TM_QW3_NSR_HE_POOL:
		case TM_QW3_NSR_HE_LSI:
			device_printf(dev,
			    "Unexpected interrupt he type: %d\n", he);
			goto end;
		case TM_QW3_NSR_HE_PHYS:
			break;
		}

		xive_cpud = DPCPU_PTR(xive_cpu_data);
		xive_write_1(sc, XIVE_TM_CPPR, cppr);

		for (;;) {
			vector = xive_read_eq(&xive_cpud->queue);

			if (vector == 0)
				break;

			if (vector == MAX_XIVE_IRQS)
				vector = xive_ipi_vector;

			powerpc_dispatch_intr(vector, tf);
		}
	}
end:
	xive_write_1(sc, XIVE_TM_CPPR, 0xff);
}