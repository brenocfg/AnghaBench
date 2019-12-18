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
struct my_softc {int /*<<< orphan*/  my_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MY_BCR ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int /*<<< orphan*/  MY_SETBIT (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int MY_SWR ; 
 int MY_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
my_reset(struct my_softc * sc)
{
	int    i;

	MY_LOCK_ASSERT(sc);
	MY_SETBIT(sc, MY_BCR, MY_SWR);
	for (i = 0; i < MY_TIMEOUT; i++) {
		DELAY(10);
		if (!(CSR_READ_4(sc, MY_BCR) & MY_SWR))
			break;
	}
	if (i == MY_TIMEOUT)
		device_printf(sc->my_dev, "reset never completed!\n");

	/* Wait a little while for the chip to get its brains in order. */
	DELAY(1000);
	return;
}