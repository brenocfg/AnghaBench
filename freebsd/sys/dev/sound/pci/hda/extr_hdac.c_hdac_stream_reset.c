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
typedef  int uint32_t ;
struct hdac_softc {int /*<<< orphan*/  mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int HDAC_READ_1 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ HDAC_SDCTL0 ; 
 int HDAC_SDCTL_SRST ; 
 int /*<<< orphan*/  HDAC_WRITE_1 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct hdac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hdac_find_stream (struct hdac_softc*,int,int) ; 

__attribute__((used)) static void
hdac_stream_reset(device_t dev, device_t child, int dir, int stream)
{
	struct hdac_softc *sc = device_get_softc(dev);
	int timeout = 1000;
	int to = timeout;
	int ss, off;
	uint32_t ctl;

	ss = hdac_find_stream(sc, dir, stream);
	KASSERT(ss >= 0,
	    ("Reset for not allocated stream (%d/%d)\n", dir, stream));

	off = ss << 5;
	ctl = HDAC_READ_1(&sc->mem, off + HDAC_SDCTL0);
	ctl |= HDAC_SDCTL_SRST;
	HDAC_WRITE_1(&sc->mem, off + HDAC_SDCTL0, ctl);
	do {
		ctl = HDAC_READ_1(&sc->mem, off + HDAC_SDCTL0);
		if (ctl & HDAC_SDCTL_SRST)
			break;
		DELAY(10);
	} while (--to);
	if (!(ctl & HDAC_SDCTL_SRST))
		device_printf(dev, "Reset setting timeout\n");
	ctl &= ~HDAC_SDCTL_SRST;
	HDAC_WRITE_1(&sc->mem, off + HDAC_SDCTL0, ctl);
	to = timeout;
	do {
		ctl = HDAC_READ_1(&sc->mem, off + HDAC_SDCTL0);
		if (!(ctl & HDAC_SDCTL_SRST))
			break;
		DELAY(10);
	} while (--to);
	if (ctl & HDAC_SDCTL_SRST)
		device_printf(dev, "Reset timeout!\n");
}