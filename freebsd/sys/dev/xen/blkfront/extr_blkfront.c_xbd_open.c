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
struct xbd_softc {int /*<<< orphan*/  xbd_users; int /*<<< orphan*/  xbd_flags; } ;
struct disk {int d_unit; struct xbd_softc* d_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  XBDF_OPEN ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
xbd_open(struct disk *dp)
{
	struct xbd_softc *sc = dp->d_drv1;

	if (sc == NULL) {
		printf("xbd%d: not found", dp->d_unit);
		return (ENXIO);
	}

	sc->xbd_flags |= XBDF_OPEN;
	sc->xbd_users++;
	return (0);
}