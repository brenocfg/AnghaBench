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
struct dpms_softc {int /*<<< orphan*/  dpms_initial_state; int /*<<< orphan*/  dpms_supported_states; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct dpms_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int dpms_get_current_state (int /*<<< orphan*/ *) ; 
 int dpms_get_supported_states (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dpms_attach(device_t dev)
{
	struct dpms_softc *sc;
	int error;

	sc = device_get_softc(dev);
	error = dpms_get_supported_states(&sc->dpms_supported_states);
	if (error)
		return (error);
	error = dpms_get_current_state(&sc->dpms_initial_state);
	return (error);
}