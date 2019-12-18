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
struct iwi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iwi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_put_firmware (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_stop (struct iwi_softc*) ; 

__attribute__((used)) static int
iwi_shutdown(device_t dev)
{
	struct iwi_softc *sc = device_get_softc(dev);

	iwi_stop(sc);
	iwi_put_firmware(sc);		/* ??? XXX */

	return 0;
}