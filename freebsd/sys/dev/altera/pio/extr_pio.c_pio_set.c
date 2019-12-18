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
struct pio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIO_OUTCLR ; 
 int /*<<< orphan*/  PIO_OUTSET ; 
 int /*<<< orphan*/  WRITE4 (struct pio_softc*,int /*<<< orphan*/ ,int) ; 
 struct pio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pio_set(device_t dev, int bit, int enable)
{
	struct pio_softc *sc;

	sc = device_get_softc(dev);

	if (enable)
		WRITE4(sc, PIO_OUTSET, bit);
	else
		WRITE4(sc, PIO_OUTCLR, bit);

	return (0);
}