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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
struct TYPE_2__ {struct resource* r_irq; } ;
struct mvs_controller {TYPE_1__ irq; int /*<<< orphan*/  r_mem; int /*<<< orphan*/  sc_iomem; } ;
struct mvs_channel {int unit; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int ATA_IRQ_RID ; 
 int HC_BASE (int) ; 
 int PORT_BASE (int) ; 
 scalar_t__ PORT_SIZE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  bus_space_subregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 struct mvs_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 struct resource* rman_reserve_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
mvs_alloc_resource(device_t dev, device_t child, int type, int *rid,
		       rman_res_t start, rman_res_t end, rman_res_t count,
		       u_int flags)
{
	struct mvs_controller *ctlr = device_get_softc(dev);
	int unit = ((struct mvs_channel *)device_get_softc(child))->unit;
	struct resource *res = NULL;
	int offset = HC_BASE(unit >> 2) + PORT_BASE(unit & 0x03);
	rman_res_t st;

	switch (type) {
	case SYS_RES_MEMORY:
		st = rman_get_start(ctlr->r_mem);
		res = rman_reserve_resource(&ctlr->sc_iomem, st + offset,
		    st + offset + PORT_SIZE - 1, PORT_SIZE, RF_ACTIVE, child);
		if (res) {
			bus_space_handle_t bsh;
			bus_space_tag_t bst;
			bsh = rman_get_bushandle(ctlr->r_mem);
			bst = rman_get_bustag(ctlr->r_mem);
			bus_space_subregion(bst, bsh, offset, PORT_SIZE, &bsh);
			rman_set_bushandle(res, bsh);
			rman_set_bustag(res, bst);
		}
		break;
	case SYS_RES_IRQ:
		if (*rid == ATA_IRQ_RID)
			res = ctlr->irq.r_irq;
		break;
	}
	return (res);
}