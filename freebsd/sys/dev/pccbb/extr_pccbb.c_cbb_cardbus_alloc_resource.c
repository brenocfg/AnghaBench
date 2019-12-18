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
typedef  int u_int ;
struct resource {int dummy; } ;
struct cbb_softc {int /*<<< orphan*/  irq_res; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource* BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int) ; 
 int CBB_MEMALIGN ; 
 int RF_ACTIVE ; 
 int RF_ALIGNMENT (int) ; 
 int RF_ALIGNMENT_MASK ; 
 int RF_SHAREABLE ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 scalar_t__ bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  cbb_insert_res (struct cbb_softc*,struct resource*,int,int) ; 
 int cbb_start_32_io ; 
 int cbb_start_mem ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int rman_get_start (int /*<<< orphan*/ ) ; 
 int rman_make_alignment_flags (int) ; 

__attribute__((used)) static struct resource *
cbb_cardbus_alloc_resource(device_t brdev, device_t child, int type,
    int *rid, rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct cbb_softc *sc = device_get_softc(brdev);
	int tmp;
	struct resource *res;
	rman_res_t align;

	switch (type) {
	case SYS_RES_IRQ:
		tmp = rman_get_start(sc->irq_res);
		if (start > tmp || end < tmp || count != 1) {
			device_printf(child, "requested interrupt %jd-%jd,"
			    "count = %jd not supported by cbb\n",
			    start, end, count);
			return (NULL);
		}
		start = end = tmp;
		flags |= RF_SHAREABLE;
		break;
	case SYS_RES_IOPORT:
		if (start <= cbb_start_32_io)
			start = cbb_start_32_io;
		if (end < start)
			end = start;
		if (count > (1 << RF_ALIGNMENT(flags)))
			flags = (flags & ~RF_ALIGNMENT_MASK) | 
			    rman_make_alignment_flags(count);
		break;
	case SYS_RES_MEMORY:
		if (start <= cbb_start_mem)
			start = cbb_start_mem;
		if (end < start)
			end = start;
		if (count < CBB_MEMALIGN)
			align = CBB_MEMALIGN;
		else
			align = count;
		if (align > (1 << RF_ALIGNMENT(flags)))
			flags = (flags & ~RF_ALIGNMENT_MASK) | 
			    rman_make_alignment_flags(align);
		break;
	}
	res = BUS_ALLOC_RESOURCE(device_get_parent(brdev), child, type, rid,
	    start, end, count, flags & ~RF_ACTIVE);
	if (res == NULL) {
		printf("cbb alloc res fail type %d rid %x\n", type, *rid);
		return (NULL);
	}
	cbb_insert_res(sc, res, type, *rid);
	if (flags & RF_ACTIVE)
		if (bus_activate_resource(child, type, *rid, res) != 0) {
			bus_release_resource(child, type, *rid, res);
			return (NULL);
		}

	return (res);
}