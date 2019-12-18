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
 int /*<<< orphan*/  PIO_DATA ; 
 int READ4 (struct pio_softc*,int /*<<< orphan*/ ) ; 
 struct pio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pio_read(device_t dev)
{
	struct pio_softc *sc;

	sc = device_get_softc(dev);

	return (READ4(sc, PIO_DATA));
}