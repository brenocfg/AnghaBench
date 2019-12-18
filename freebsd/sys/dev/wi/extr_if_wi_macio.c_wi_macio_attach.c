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
struct wi_softc {scalar_t__ wi_bus_type; scalar_t__ wi_gone; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (struct wi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WI_EVENT_ACK ; 
 int /*<<< orphan*/  WI_INT_EN ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct wi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macio_enable_wireless (int /*<<< orphan*/ ,int) ; 
 int wi_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wi_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wi_macio_attach(device_t dev)
{
	struct wi_softc	*sc;
	int error;

	sc = device_get_softc(dev);
	sc->wi_gone = 0;
	sc->wi_bus_type = 0;

	error = wi_alloc(dev, 0);
	if (error == 0) {
		macio_enable_wireless(device_get_parent(dev), 1);
		/* Make sure interrupts are disabled. */
		CSR_WRITE_2(sc, WI_INT_EN, 0);
		CSR_WRITE_2(sc, WI_EVENT_ACK, 0xFFFF);

		error = wi_attach(dev);
		if (error != 0)
			wi_free(dev);
	}
	return error;
}