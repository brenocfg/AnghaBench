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
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_mbox_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  TI_MBOX_FIFOSTATUS (int) ; 
 int /*<<< orphan*/  TI_MBOX_LOCK (struct ti_mbox_softc*) ; 
 int /*<<< orphan*/  TI_MBOX_MESSAGE (int) ; 
 int /*<<< orphan*/  TI_MBOX_UNLOCK (struct ti_mbox_softc*) ; 
 struct ti_mbox_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int ti_mbox_reg_read (struct ti_mbox_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_mbox_reg_write (struct ti_mbox_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_mbox_write(device_t dev, int chan, uint32_t data)
{
	int limit = 500;
	struct ti_mbox_softc *sc;

	if (chan < 0 || chan > 7)
		return (EINVAL);
	sc = device_get_softc(dev);
	TI_MBOX_LOCK(sc);
	/* XXX implement interrupt method */
	while (ti_mbox_reg_read(sc, TI_MBOX_FIFOSTATUS(chan)) == 1 && 
	    limit--) {
		DELAY(10);
	}
	if (limit == 0) {
		device_printf(dev, "FIFOSTAUS%d stuck\n", chan);
		TI_MBOX_UNLOCK(sc);
		return (EAGAIN);
	}
	ti_mbox_reg_write(sc, TI_MBOX_MESSAGE(chan), data);

	return (0);
}