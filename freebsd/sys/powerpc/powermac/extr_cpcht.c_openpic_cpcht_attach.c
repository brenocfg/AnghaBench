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
struct openpic_cpcht_softc {int /*<<< orphan*/  sc_ht_mtx; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int /*<<< orphan*/  INTR_TRIGGER_LEVEL ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  cpcht_msipic ; 
 struct openpic_cpcht_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (scalar_t__) ; 
 int openpic_common_attach (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openpic_config (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ root_pic ; 

__attribute__((used)) static int
openpic_cpcht_attach(device_t dev)
{
	struct openpic_cpcht_softc *sc;
	phandle_t node;
	int err, irq;

	node = ofw_bus_get_node(dev);
	err = openpic_common_attach(dev, node);
	if (err != 0)
		return (err);

	/*
	 * The HT APIC stuff is not thread-safe, so we need a mutex to
	 * protect it.
	 */
	sc = device_get_softc(dev);
	mtx_init(&sc->sc_ht_mtx, "htpic", NULL, MTX_SPIN);

	/*
	 * Interrupts 0-3 are internally sourced and are level triggered
	 * active low. Interrupts 4-123 are connected to a pulse generator
	 * and should be programmed as edge triggered low-to-high.
	 * 
	 * IBM CPC945 Manual, Section 9.3.
	 */

	for (irq = 0; irq < 4; irq++)
		openpic_config(dev, irq, INTR_TRIGGER_LEVEL, INTR_POLARITY_LOW);
	for (irq = 4; irq < 124; irq++)
		openpic_config(dev, irq, INTR_TRIGGER_EDGE, INTR_POLARITY_LOW);

	/*
	 * Use this PIC for MSI only if it is the root PIC. This may not
	 * be necessary, but Linux does it, and I cannot find any U3 machines
	 * with MSI devices to test.
	 */
	if (dev == root_pic)
		cpcht_msipic = node;

	return (0);
}