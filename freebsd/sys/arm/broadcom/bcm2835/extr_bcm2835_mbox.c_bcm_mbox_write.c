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
struct bcm_mbox_softc {scalar_t__* have_message; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  MBOX_LOCK (struct bcm_mbox_softc*) ; 
 int /*<<< orphan*/  MBOX_MSG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_UNLOCK (struct bcm_mbox_softc*) ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int /*<<< orphan*/  REG_WRITE ; 
 int STATUS_FULL ; 
 struct bcm_mbox_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int,int /*<<< orphan*/ ) ; 
 int mbox_read_4 (struct bcm_mbox_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_write_4 (struct bcm_mbox_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
bcm_mbox_write(device_t dev, int chan, uint32_t data)
{
	int limit = 1000;
	struct bcm_mbox_softc *sc = device_get_softc(dev);

	dprintf("bcm_mbox_write: chan %d, data %08x\n", chan, data);
	MBOX_LOCK(sc);
	sc->have_message[chan] = 0;
	while ((mbox_read_4(sc, REG_STATUS) & STATUS_FULL) && --limit)
		DELAY(5);
	if (limit == 0) {
		printf("bcm_mbox_write: STATUS_FULL stuck");
		MBOX_UNLOCK(sc);
		return (EAGAIN);
	}
	mbox_write_4(sc, REG_WRITE, MBOX_MSG(chan, data));
	MBOX_UNLOCK(sc);

	return (0);
}