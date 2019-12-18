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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct fman_softc {int /*<<< orphan*/  mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct fman_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 

int
fman_get_bushandle(device_t dev, vm_offset_t *fm_base)
{
	struct fman_softc *sc = device_get_softc(dev);

	*fm_base = rman_get_bushandle(sc->mem_res);

	return (0);
}