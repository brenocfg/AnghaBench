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
typedef  scalar_t__ u_int32_t ;
struct ida_softc {int regs_res_id; int /*<<< orphan*/  ih; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_res_type; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/ * regs; int /*<<< orphan*/  regs_res_type; int /*<<< orphan*/  lock; int /*<<< orphan*/  ch; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/  dev; } ;
struct ida_board {int /*<<< orphan*/  flags; int /*<<< orphan*/ * accessor; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int ENOMEM ; 
 scalar_t__ IDA_DEVICEID_DEC_SMART ; 
 int IDA_PCI_MEMADDR ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ida_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ida_free (struct ida_softc*) ; 
 int /*<<< orphan*/  ida_intr ; 
 struct ida_board* ida_pci_match (int /*<<< orphan*/ ) ; 
 int ida_setup (struct ida_softc*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ida_pci_attach(device_t dev)
{
	struct ida_board *board = ida_pci_match(dev);
	u_int32_t id = pci_get_devid(dev);
	struct ida_softc *ida;
	int error, rid;

	ida = (struct ida_softc *)device_get_softc(dev);
	ida->dev = dev;
	ida->cmd = *board->accessor;
	ida->flags = board->flags;
	mtx_init(&ida->lock, "ida", NULL, MTX_DEF);
	callout_init_mtx(&ida->ch, &ida->lock, 0);

	ida->regs_res_type = SYS_RES_MEMORY;
	ida->regs_res_id = IDA_PCI_MEMADDR;
	if (id == IDA_DEVICEID_DEC_SMART)
		ida->regs_res_id = PCIR_BAR(0);

	ida->regs = bus_alloc_resource_any(dev, ida->regs_res_type,
	    &ida->regs_res_id, RF_ACTIVE);
	if (ida->regs == NULL) {
		device_printf(dev, "can't allocate memory resources\n");
		return (ENOMEM);
	}

	error = bus_dma_tag_create(
		/* parent	*/ bus_get_dma_tag(dev),
		/* alignment	*/ 1,
		/* boundary	*/ 0,
		/* lowaddr	*/ BUS_SPACE_MAXADDR_32BIT,
		/* highaddr	*/ BUS_SPACE_MAXADDR,
		/* filter	*/ NULL,
		/* filterarg	*/ NULL,
		/* maxsize	*/ BUS_SPACE_MAXSIZE_32BIT,
		/* nsegments	*/ BUS_SPACE_UNRESTRICTED,
		/* maxsegsize	*/ BUS_SPACE_MAXSIZE_32BIT,
		/* flags	*/ BUS_DMA_ALLOCNOW,
		/* lockfunc	*/ NULL,
		/* lockarg	*/ NULL,
		&ida->parent_dmat);
	if (error != 0) {
		device_printf(dev, "can't allocate DMA tag\n");
		ida_free(ida);
		return (ENOMEM);
	}

	rid = 0;
	ida->irq_res_type = SYS_RES_IRQ;
	ida->irq = bus_alloc_resource_any(dev, ida->irq_res_type, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (ida->irq == NULL) {
	        ida_free(ida);
	        return (ENOMEM);
	}
	error = bus_setup_intr(dev, ida->irq, INTR_TYPE_BIO | INTR_ENTROPY | INTR_MPSAFE,
	    NULL, ida_intr, ida, &ida->ih);
	if (error) {
		device_printf(dev, "can't setup interrupt\n");
		ida_free(ida);
		return (ENOMEM);
	}

	error = ida_setup(ida);
	if (error) {
	        ida_free(ida);
	        return (error);
	}

	return (0);
}