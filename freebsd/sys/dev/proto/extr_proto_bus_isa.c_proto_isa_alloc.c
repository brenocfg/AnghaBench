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
struct resource {int dummy; } ;
struct proto_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PROTO_RES_BUSDMA ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SYS_RES_DRQ ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 struct proto_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_add_resource (struct proto_softc*,int,int,struct resource*) ; 

__attribute__((used)) static int
proto_isa_alloc(device_t dev, int type, int nrids)
{
	struct resource *res;
	struct proto_softc *sc;
	int count, rid;

	sc = device_get_softc(dev);
	count = 0;
	for (rid = 0; rid < nrids; rid++) {
		res = bus_alloc_resource_any(dev, type, &rid, RF_ACTIVE);
		if (res == NULL)
			break;
		proto_add_resource(sc, type, rid, res);
		count++;
	}
	if (type == SYS_RES_DRQ && count > 0)
		proto_add_resource(sc, PROTO_RES_BUSDMA, 0, NULL);
	return (count);
}