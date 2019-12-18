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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct cuda_softc {int sc_autopoll; int /*<<< orphan*/  sc_mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CMD_AUTOPOLL ; 
 int CUDA_PSEUDO ; 
 int /*<<< orphan*/  cuda_send (struct cuda_softc*,int,int,int*) ; 
 struct cuda_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int 
cuda_adb_autopoll(device_t dev, uint16_t mask) {
	struct cuda_softc *sc = device_get_softc(dev);

	uint8_t cmd[] = {CUDA_PSEUDO, CMD_AUTOPOLL, mask != 0};

	mtx_lock(&sc->sc_mutex);

	if (cmd[2] == sc->sc_autopoll) {
		mtx_unlock(&sc->sc_mutex);
		return (0);
	}

	sc->sc_autopoll = -1;
	cuda_send(sc, 1, 3, cmd);

	mtx_unlock(&sc->sc_mutex);

	return (0);
}