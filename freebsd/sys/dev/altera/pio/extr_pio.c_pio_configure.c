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
 int /*<<< orphan*/  PIO_DIR ; 
 int /*<<< orphan*/  PIO_INT_MASK ; 
 int /*<<< orphan*/  WRITE4 (struct pio_softc*,int /*<<< orphan*/ ,int) ; 
 struct pio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pio_configure(device_t dev, int dir, int mask)
{
	struct pio_softc *sc;

	sc = device_get_softc(dev);

	WRITE4(sc, PIO_INT_MASK, mask);
	WRITE4(sc, PIO_DIR, dir);

	return (0);
}