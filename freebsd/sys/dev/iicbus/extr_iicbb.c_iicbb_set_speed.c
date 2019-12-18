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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct iicbb_softc {int /*<<< orphan*/  udelay; int /*<<< orphan*/  iicbus; } ;

/* Variables and functions */
 int IICBUS_GET_FREQUENCY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (int,int) ; 

__attribute__((used)) static void
iicbb_set_speed(struct iicbb_softc *sc, u_char speed)
{
	u_int busfreq, period;

	/*
	 * NB: the resulting frequency will be a quarter (even less) of the
	 * configured bus frequency.  This is for historic reasons.  The default
	 * bus frequency is 100 kHz.  And the historic default udelay is 10
	 * microseconds.  The cycle of sending a bit takes four udelay-s plus
	 * SCL is kept low for extra two udelay-s.  The actual I/O toggling also
	 * has an overhead.
	 */
	busfreq = IICBUS_GET_FREQUENCY(sc->iicbus, speed);
	period = 1000000 / busfreq;	/* Hz -> uS */
	sc->udelay = MAX(period, 1);
}