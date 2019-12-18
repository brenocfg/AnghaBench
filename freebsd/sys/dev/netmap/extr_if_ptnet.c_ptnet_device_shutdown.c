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
struct ptnet_softc {int /*<<< orphan*/  iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTNETMAP_PTCTL_DELETE ; 
 int /*<<< orphan*/  PTNET_IO_CSB_GH_BAH ; 
 int /*<<< orphan*/  PTNET_IO_CSB_GH_BAL ; 
 int /*<<< orphan*/  PTNET_IO_CSB_HG_BAH ; 
 int /*<<< orphan*/  PTNET_IO_CSB_HG_BAL ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptnet_nm_ptctl (struct ptnet_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptnet_device_shutdown(struct ptnet_softc *sc)
{
	ptnet_nm_ptctl(sc, PTNETMAP_PTCTL_DELETE);
	bus_write_4(sc->iomem, PTNET_IO_CSB_GH_BAH, 0);
	bus_write_4(sc->iomem, PTNET_IO_CSB_GH_BAL, 0);
	bus_write_4(sc->iomem, PTNET_IO_CSB_HG_BAH, 0);
	bus_write_4(sc->iomem, PTNET_IO_CSB_HG_BAL, 0);
}