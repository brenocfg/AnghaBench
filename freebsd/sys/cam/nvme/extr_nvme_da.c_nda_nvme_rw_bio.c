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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct nda_softc {int /*<<< orphan*/  nsid; TYPE_1__* disk; } ;
struct ccb_nvmeio {int /*<<< orphan*/  cmd; } ;
struct bio {int bio_flags; scalar_t__ bio_bcount; int /*<<< orphan*/  bio_pblkno; void* bio_data; } ;
struct TYPE_2__ {scalar_t__ d_sectorsize; } ;

/* Variables and functions */
 int BIO_UNMAPPED ; 
 int CAM_DATA_BIO ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_OUT ; 
 scalar_t__ NVME_OPC_READ ; 
 int /*<<< orphan*/  cam_fill_nvmeio (struct ccb_nvmeio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,scalar_t__,int) ; 
 int nda_default_timeout ; 
 int /*<<< orphan*/  ndadone ; 
 int /*<<< orphan*/  nvme_ns_rw_cmd (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
nda_nvme_rw_bio(struct nda_softc *softc, struct ccb_nvmeio *nvmeio,
    struct bio *bp, uint32_t rwcmd)
{
	int flags = rwcmd == NVME_OPC_READ ? CAM_DIR_IN : CAM_DIR_OUT;
	void *payload;
	uint64_t lba;
	uint32_t count;

	if (bp->bio_flags & BIO_UNMAPPED) {
		flags |= CAM_DATA_BIO;
		payload = bp;
	} else {
		payload = bp->bio_data;
	}

	lba = bp->bio_pblkno;
	count = bp->bio_bcount / softc->disk->d_sectorsize;

	cam_fill_nvmeio(nvmeio,
	    0,			/* retries */
	    ndadone,		/* cbfcnp */
	    flags,		/* flags */
	    payload,		/* data_ptr */
	    bp->bio_bcount,	/* dxfer_len */
	    nda_default_timeout * 1000); /* timeout 30s */
	nvme_ns_rw_cmd(&nvmeio->cmd, rwcmd, softc->nsid, lba, count);
}