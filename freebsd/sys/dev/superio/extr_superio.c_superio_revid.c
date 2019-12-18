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
typedef  int /*<<< orphan*/  uint8_t ;
struct siosc {int /*<<< orphan*/  revid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct siosc* device_get_softc (int /*<<< orphan*/ ) ; 

uint8_t
superio_revid(device_t dev)
{
	device_t sio_dev = device_get_parent(dev);
	struct siosc *sc = device_get_softc(sio_dev);

	return (sc->revid);
}