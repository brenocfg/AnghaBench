#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kern_data_ptr; } ;
union ctl_io {TYPE_2__ scsiio; } ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ctl_lba_len_flags {int flags; int lba; scalar_t__ len; } ;
struct ctl_be_lun {int blocksize; int pblockexp; int pblockoff; } ;
struct ctl_be_block_lun {int /*<<< orphan*/  (* dispatch ) (struct ctl_be_block_lun*,struct ctl_be_block_io*) ;int /*<<< orphan*/  lun_zone; struct ctl_be_lun cbe_lun; int /*<<< orphan*/  (* unmap ) (struct ctl_be_block_lun*,struct ctl_be_block_io*) ;} ;
struct ctl_be_block_io {int io_offset; int io_len; int /*<<< orphan*/  beio_cont; TYPE_1__* sg_segs; int /*<<< orphan*/  num_segs; int /*<<< orphan*/  ds_trans_type; int /*<<< orphan*/  bio_cmd; int /*<<< orphan*/  io; } ;
struct TYPE_6__ {scalar_t__ ptr; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 struct ctl_lba_len_flags* ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_DELETE ; 
 int /*<<< orphan*/  BIO_WRITE ; 
 int /*<<< orphan*/  CTLBLK_MAX_SEG ; 
 int CTLBLK_MAX_SEGS ; 
 int /*<<< orphan*/  DEVSTAT_FREE ; 
 int /*<<< orphan*/  DEVSTAT_WRITE ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 TYPE_3__* PRIV (union ctl_io*) ; 
 int SWS_ANCHOR ; 
 int SWS_LBDATA ; 
 int SWS_NDOB ; 
 int SWS_UNMAP ; 
 int /*<<< orphan*/  ctl_be_block_cw_done_ws ; 
 int /*<<< orphan*/  ctl_config_write_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_free_beio (struct ctl_be_block_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (TYPE_2__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ctl_be_block_lun*,struct ctl_be_block_io*) ; 
 int /*<<< orphan*/  stub2 (struct ctl_be_block_lun*,struct ctl_be_block_io*) ; 
 int /*<<< orphan*/ * uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_be_block_cw_dispatch_ws(struct ctl_be_block_lun *be_lun,
			    union ctl_io *io)
{
	struct ctl_be_lun *cbe_lun = &be_lun->cbe_lun;
	struct ctl_be_block_io *beio;
	struct ctl_lba_len_flags *lbalen;
	uint64_t len_left, lba;
	uint32_t pb, pbo, adj;
	int i, seglen;
	uint8_t *buf, *end;

	DPRINTF("entered\n");

	beio = (struct ctl_be_block_io *)PRIV(io)->ptr;
	lbalen = ARGS(beio->io);

	if (lbalen->flags & ~(SWS_LBDATA | SWS_UNMAP | SWS_ANCHOR | SWS_NDOB) ||
	    (lbalen->flags & (SWS_UNMAP | SWS_ANCHOR) && be_lun->unmap == NULL)) {
		ctl_free_beio(beio);
		ctl_set_invalid_field(&io->scsiio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ 1,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		ctl_config_write_done(io);
		return;
	}

	if (lbalen->flags & (SWS_UNMAP | SWS_ANCHOR)) {
		beio->io_offset = lbalen->lba * cbe_lun->blocksize;
		beio->io_len = (uint64_t)lbalen->len * cbe_lun->blocksize;
		beio->bio_cmd = BIO_DELETE;
		beio->ds_trans_type = DEVSTAT_FREE;

		be_lun->unmap(be_lun, beio);
		return;
	}

	beio->bio_cmd = BIO_WRITE;
	beio->ds_trans_type = DEVSTAT_WRITE;

	DPRINTF("WRITE SAME at LBA %jx len %u\n",
	       (uintmax_t)lbalen->lba, lbalen->len);

	pb = cbe_lun->blocksize << be_lun->cbe_lun.pblockexp;
	if (be_lun->cbe_lun.pblockoff > 0)
		pbo = pb - cbe_lun->blocksize * be_lun->cbe_lun.pblockoff;
	else
		pbo = 0;
	len_left = (uint64_t)lbalen->len * cbe_lun->blocksize;
	for (i = 0, lba = 0; i < CTLBLK_MAX_SEGS && len_left > 0; i++) {

		/*
		 * Setup the S/G entry for this chunk.
		 */
		seglen = MIN(CTLBLK_MAX_SEG, len_left);
		if (pb > cbe_lun->blocksize) {
			adj = ((lbalen->lba + lba) * cbe_lun->blocksize +
			    seglen - pbo) % pb;
			if (seglen > adj)
				seglen -= adj;
			else
				seglen -= seglen % cbe_lun->blocksize;
		} else
			seglen -= seglen % cbe_lun->blocksize;
		beio->sg_segs[i].len = seglen;
		beio->sg_segs[i].addr = uma_zalloc(be_lun->lun_zone, M_WAITOK);

		DPRINTF("segment %d addr %p len %zd\n", i,
			beio->sg_segs[i].addr, beio->sg_segs[i].len);

		beio->num_segs++;
		len_left -= seglen;

		buf = beio->sg_segs[i].addr;
		end = buf + seglen;
		for (; buf < end; buf += cbe_lun->blocksize) {
			if (lbalen->flags & SWS_NDOB) {
				memset(buf, 0, cbe_lun->blocksize);
			} else {
				memcpy(buf, io->scsiio.kern_data_ptr,
				    cbe_lun->blocksize);
			}
			if (lbalen->flags & SWS_LBDATA)
				scsi_ulto4b(lbalen->lba + lba, buf);
			lba++;
		}
	}

	beio->io_offset = lbalen->lba * cbe_lun->blocksize;
	beio->io_len = lba * cbe_lun->blocksize;

	/* We can not do all in one run. Correct and schedule rerun. */
	if (len_left > 0) {
		lbalen->lba += lba;
		lbalen->len -= lba;
		beio->beio_cont = ctl_be_block_cw_done_ws;
	}

	be_lun->dispatch(be_lun, beio);
}