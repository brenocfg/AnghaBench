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
struct sbuf {int dummy; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_isa_devnames ; 
 int /*<<< orphan*/  proto_isa_prefix ; 
 int proto_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proto_isa_probe(device_t dev)
{
	struct sbuf *sb;
	struct resource *res;
	int rid, type;

	rid = 0;
	type = SYS_RES_IOPORT;
	res = bus_alloc_resource_any(dev, type, &rid, RF_ACTIVE);
	if (res == NULL) {
		type = SYS_RES_MEMORY;
		res = bus_alloc_resource_any(dev, type, &rid, RF_ACTIVE);
	}
	if (res == NULL)
		return (ENODEV);

	sb = sbuf_new_auto();
	sbuf_printf(sb, "%s:%#jx", proto_isa_prefix, rman_get_start(res));
	sbuf_finish(sb);
	device_set_desc_copy(dev, sbuf_data(sb));
	sbuf_delete(sb);
	bus_release_resource(dev, type, rid, res);
	return (proto_probe(dev, proto_isa_prefix, &proto_isa_devnames));
}