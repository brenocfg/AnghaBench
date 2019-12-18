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
struct abtn_softc {int /*<<< orphan*/  handler_id; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  adb_get_device_handler (int /*<<< orphan*/ ) ; 
 struct abtn_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
abtn_attach(device_t dev) 
{
	struct abtn_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	sc->handler_id = adb_get_device_handler(dev);

	return 0;
}