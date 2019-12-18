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
typedef  int /*<<< orphan*/  u_char ;
struct iicoc_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iicoc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int iicoc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iicoc_reset(device_t dev, u_char speed, u_char addr, u_char *oldadr)
{
	int error;
	struct iicoc_softc *sc;

	sc = device_get_softc(dev);
	mtx_lock(&sc->sc_mtx);
	error = iicoc_init(dev);
	mtx_unlock(&sc->sc_mtx);
	return (error);
}