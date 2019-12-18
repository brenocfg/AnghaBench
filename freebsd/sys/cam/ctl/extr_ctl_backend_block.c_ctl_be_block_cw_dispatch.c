#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tag_type; int* cdb; } ;
union ctl_io {TYPE_1__ scsiio; } ;
struct ctl_be_block_softc {int dummy; } ;
struct ctl_be_block_lun {struct ctl_be_block_softc* softc; } ;
struct ctl_be_block_io {int /*<<< orphan*/  ds_tag_type; int /*<<< orphan*/  beio_cont; struct ctl_be_block_lun* lun; union ctl_io* io; } ;
struct TYPE_4__ {void* ptr; } ;

/* Variables and functions */
#define  CTL_TAG_ACA 137 
#define  CTL_TAG_HEAD_OF_QUEUE 136 
#define  CTL_TAG_ORDERED 135 
#define  CTL_TAG_SIMPLE 134 
#define  CTL_TAG_UNTAGGED 133 
 int /*<<< orphan*/  DEVSTAT_TAG_HEAD ; 
 int /*<<< orphan*/  DEVSTAT_TAG_ORDERED ; 
 int /*<<< orphan*/  DEVSTAT_TAG_SIMPLE ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 TYPE_2__* PRIV (union ctl_io*) ; 
#define  SYNCHRONIZE_CACHE 132 
#define  SYNCHRONIZE_CACHE_16 131 
#define  UNMAP 130 
#define  WRITE_SAME_10 129 
#define  WRITE_SAME_16 128 
 struct ctl_be_block_io* ctl_alloc_beio (struct ctl_be_block_softc*) ; 
 int /*<<< orphan*/  ctl_be_block_cw_dispatch_sync (struct ctl_be_block_lun*,union ctl_io*) ; 
 int /*<<< orphan*/  ctl_be_block_cw_dispatch_unmap (struct ctl_be_block_lun*,union ctl_io*) ; 
 int /*<<< orphan*/  ctl_be_block_cw_dispatch_ws (struct ctl_be_block_lun*,union ctl_io*) ; 
 int /*<<< orphan*/  ctl_be_block_cw_done ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static void
ctl_be_block_cw_dispatch(struct ctl_be_block_lun *be_lun,
			 union ctl_io *io)
{
	struct ctl_be_block_io *beio;
	struct ctl_be_block_softc *softc;

	DPRINTF("entered\n");

	softc = be_lun->softc;
	beio = ctl_alloc_beio(softc);
	beio->io = io;
	beio->lun = be_lun;
	beio->beio_cont = ctl_be_block_cw_done;
	switch (io->scsiio.tag_type) {
	case CTL_TAG_ORDERED:
		beio->ds_tag_type = DEVSTAT_TAG_ORDERED;
		break;
	case CTL_TAG_HEAD_OF_QUEUE:
		beio->ds_tag_type = DEVSTAT_TAG_HEAD;
		break;
	case CTL_TAG_UNTAGGED:
	case CTL_TAG_SIMPLE:
	case CTL_TAG_ACA:
	default:
		beio->ds_tag_type = DEVSTAT_TAG_SIMPLE;
		break;
	}
	PRIV(io)->ptr = (void *)beio;

	switch (io->scsiio.cdb[0]) {
	case SYNCHRONIZE_CACHE:
	case SYNCHRONIZE_CACHE_16:
		ctl_be_block_cw_dispatch_sync(be_lun, io);
		break;
	case WRITE_SAME_10:
	case WRITE_SAME_16:
		ctl_be_block_cw_dispatch_ws(be_lun, io);
		break;
	case UNMAP:
		ctl_be_block_cw_dispatch_unmap(be_lun, io);
		break;
	default:
		panic("Unhandled CDB type %#x", io->scsiio.cdb[0]);
		break;
	}
}