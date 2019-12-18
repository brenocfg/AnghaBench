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
struct xpcib_softc {uintptr_t bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  PCIB_IVAR_BUS 128 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xpcib_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct xpcib_softc *sc = (struct xpcib_softc *)device_get_softc(dev);
	switch (which) {
	case  PCIB_IVAR_BUS:
		*result = sc->bus;
		return 0;
	}
	return ENOENT;
}