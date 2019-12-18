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
struct mv_pcib_softc {uintptr_t sc_busnr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  PCIB_IVAR_BUS 128 
 struct mv_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_pcib_write_ivar(device_t dev, device_t child, int which, uintptr_t value)
{
	struct mv_pcib_softc *sc = device_get_softc(dev);

	switch (which) {
	case PCIB_IVAR_BUS:
		sc->sc_busnr = value;
		return (0);
	}

	return (ENOENT);
}