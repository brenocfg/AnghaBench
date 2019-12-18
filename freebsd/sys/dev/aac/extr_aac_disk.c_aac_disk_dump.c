#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct disk {struct aac_disk* d_drv1; } ;
struct aac_softc {int aac_max_sectors; int flags; int /*<<< orphan*/  aac_buffer_dmat; int /*<<< orphan*/  aac_dev; TYPE_1__* aac_common; } ;
struct TYPE_8__ {scalar_t__ Size; } ;
struct aac_fib {TYPE_4__ Header; int /*<<< orphan*/ * data; } ;
struct aac_disk {TYPE_3__* ad_container; struct aac_softc* ad_controller; } ;
struct aac_blockwrite64 {size_t BlockNumber; size_t SectorCount; scalar_t__ Flags; scalar_t__ Pad; int /*<<< orphan*/  ContainerId; int /*<<< orphan*/  Command; } ;
struct aac_blockwrite {size_t BlockNumber; size_t ByteCount; int /*<<< orphan*/  Stable; int /*<<< orphan*/  ContainerId; int /*<<< orphan*/  Command; } ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dmamap_callback_t ;
struct TYPE_6__ {int /*<<< orphan*/  ObjectId; } ;
struct TYPE_7__ {TYPE_2__ co_mntobj; } ;
struct TYPE_5__ {struct aac_fib ac_sync_fib; } ;

/* Variables and functions */
 size_t AAC_BLOCK_SIZE ; 
 int AAC_FLAGS_SG_64BIT ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  CUNSTABLE ; 
 int /*<<< orphan*/  ContainerCommand ; 
 int /*<<< orphan*/  ContainerCommand64 ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  VM_CtBlockWrite ; 
 int /*<<< orphan*/  VM_CtHostWrite64 ; 
 int /*<<< orphan*/ * aac_dump_map_sg ; 
 int /*<<< orphan*/ * aac_dump_map_sg64 ; 
 scalar_t__ aac_sync_fib (struct aac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aac_fib*,int) ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *,struct aac_fib*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
aac_disk_dump(void *arg, void *virtual, vm_offset_t physical, off_t offset, size_t length)
{
	struct aac_disk *ad;
	struct aac_softc *sc;
	struct aac_fib *fib;
	size_t len, maxio;
	int size;
	static bus_dmamap_t dump_datamap;
	static int first = 0;
	struct disk *dp;
	bus_dmamap_callback_t *callback;
	u_int32_t command;

	dp = arg;
	ad = dp->d_drv1;

	if (ad == NULL)
		return (EINVAL);

	sc= ad->ad_controller;

	if (!first) {
		first = 1;
		if (bus_dmamap_create(sc->aac_buffer_dmat, 0, &dump_datamap)) {
			device_printf(sc->aac_dev,
			    "bus_dmamap_create failed\n");
			return (ENOMEM);
		}
	}

	/* Skip aac_alloc_sync_fib().  We don't want to mess with sleep locks */
	fib = &sc->aac_common->ac_sync_fib;

	while (length > 0) {
		maxio = sc->aac_max_sectors << 9;
		len = (length > maxio) ? maxio : length;
		if ((sc->flags & AAC_FLAGS_SG_64BIT) == 0) {
			struct aac_blockwrite *bw;
			bw = (struct aac_blockwrite *)&fib->data[0];
			bw->Command = VM_CtBlockWrite;
			bw->ContainerId = ad->ad_container->co_mntobj.ObjectId;
			bw->BlockNumber = offset / AAC_BLOCK_SIZE;
			bw->ByteCount = len;
			bw->Stable = CUNSTABLE;
			command = ContainerCommand;
			callback = aac_dump_map_sg;
			size = sizeof(struct aac_blockwrite);
		} else {
			struct aac_blockwrite64 *bw;
			bw = (struct aac_blockwrite64 *)&fib->data[0];
			bw->Command = VM_CtHostWrite64;
			bw->ContainerId = ad->ad_container->co_mntobj.ObjectId;
			bw->BlockNumber = offset / AAC_BLOCK_SIZE;
			bw->SectorCount = len / AAC_BLOCK_SIZE;
			bw->Pad = 0;
			bw->Flags = 0;
			command = ContainerCommand64;
			callback = aac_dump_map_sg64;
			size = sizeof(struct aac_blockwrite64);
		}

		/*
		 * There really isn't any way to recover from errors or
		 * resource shortages here.  Oh well.  Because of that, don't
		 * bother trying to send the command from the callback; there
		 * is too much required context.
		 */
		if (bus_dmamap_load(sc->aac_buffer_dmat, dump_datamap, virtual,
		    len, callback, fib, BUS_DMA_NOWAIT) != 0)
			return (ENOMEM);

		bus_dmamap_sync(sc->aac_buffer_dmat, dump_datamap,
		    BUS_DMASYNC_PREWRITE);

		/* fib->Header.Size is set in aac_dump_map_sg */
		size += fib->Header.Size;

		if (aac_sync_fib(sc, command, 0, fib, size)) {
			device_printf(sc->aac_dev,
			     "Error dumping block 0x%jx\n",
			     (uintmax_t)physical);
			return (EIO);
		}

		bus_dmamap_sync(sc->aac_buffer_dmat, dump_datamap,
		    BUS_DMASYNC_POSTWRITE);

		bus_dmamap_unload(sc->aac_buffer_dmat, dump_datamap);

		length -= len;
		offset += len;
		virtual = (uint8_t *)virtual + len;
	}

	return (0);
}