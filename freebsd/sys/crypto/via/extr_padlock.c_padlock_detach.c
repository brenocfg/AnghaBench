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
struct padlock_softc {int /*<<< orphan*/  sc_cid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct padlock_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
padlock_detach(device_t dev)
{
	struct padlock_softc *sc = device_get_softc(dev);

	crypto_unregister_all(sc->sc_cid);
	return (0);
}