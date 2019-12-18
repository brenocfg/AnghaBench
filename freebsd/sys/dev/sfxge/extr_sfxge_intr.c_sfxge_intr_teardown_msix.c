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
struct TYPE_2__ {struct resource* msix_res; } ;
struct sfxge_softc {TYPE_1__ intr; int /*<<< orphan*/  dev; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int rman_get_rid (struct resource*) ; 

__attribute__((used)) static void
sfxge_intr_teardown_msix(struct sfxge_softc *sc)
{
	device_t dev;
	struct resource *resp;
	int rid;

	dev = sc->dev;
	resp = sc->intr.msix_res;

	rid = rman_get_rid(resp);
	bus_release_resource(dev, SYS_RES_MEMORY, rid, resp);
}