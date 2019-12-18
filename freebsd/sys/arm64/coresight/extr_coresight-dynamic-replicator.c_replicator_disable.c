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
struct replicator_softc {int /*<<< orphan*/  res; } ;
struct endpoint {int dummy; } ;
struct coresight_event {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  REPLICATOR_IDFILTER0 ; 
 int /*<<< orphan*/  REPLICATOR_IDFILTER1 ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct replicator_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
replicator_disable(device_t dev, struct endpoint *endp,
    struct coresight_event *event)
{
	struct replicator_softc *sc;

	sc = device_get_softc(dev);

	bus_write_4(sc->res, REPLICATOR_IDFILTER0, 0xff);
	bus_write_4(sc->res, REPLICATOR_IDFILTER1, 0xff);
}