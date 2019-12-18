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
struct vtblk_softc {int vtblk_flags; } ;
struct disk {struct vtblk_softc* d_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int VTBLK_FLAG_DETACH ; 

__attribute__((used)) static int
vtblk_open(struct disk *dp)
{
	struct vtblk_softc *sc;

	if ((sc = dp->d_drv1) == NULL)
		return (ENXIO);

	return (sc->vtblk_flags & VTBLK_FLAG_DETACH ? ENXIO : 0);
}