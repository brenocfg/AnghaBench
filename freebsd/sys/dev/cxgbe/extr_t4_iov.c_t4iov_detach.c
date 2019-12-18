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
struct t4iov_softc {scalar_t__ sc_attached; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct t4iov_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int t4iov_detach_child (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
t4iov_detach(device_t dev)
{
	struct t4iov_softc *sc;
	int error;

	sc = device_get_softc(dev);
	if (sc->sc_attached) {
		error = t4iov_detach_child(dev);
		if (error)
			return (error);
	}
	return (0);
}