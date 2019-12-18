#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {uintptr_t sec; } ;
struct cbb_softc {uintptr_t domain; TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  PCIB_IVAR_BUS 129 
#define  PCIB_IVAR_DOMAIN 128 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
cbb_read_ivar(device_t brdev, device_t child, int which, uintptr_t *result)
{
	struct cbb_softc *sc = device_get_softc(brdev);

	switch (which) {
	case PCIB_IVAR_DOMAIN:
		*result = sc->domain;
		return (0);
	case PCIB_IVAR_BUS:
		*result = sc->bus.sec;
		return (0);
	}
	return (ENOENT);
}