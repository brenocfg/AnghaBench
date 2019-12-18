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
typedef  int /*<<< orphan*/  u_int ;
struct cuda_softc {scalar_t__ sc_state; int /*<<< orphan*/  sc_waiting; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CUDA_IDLE ; 
 int /*<<< orphan*/  cuda_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_intr_state (struct cuda_softc*) ; 
 struct cuda_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
cuda_poll(device_t dev)
{
	struct cuda_softc *sc = device_get_softc(dev);

	if (sc->sc_state == CUDA_IDLE && !cuda_intr_state(sc) && 
	    !sc->sc_waiting)
		return (0);

	cuda_intr(dev);
	return (0);
}