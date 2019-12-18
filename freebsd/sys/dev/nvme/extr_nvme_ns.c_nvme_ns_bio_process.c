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
typedef  int uint32_t ;
struct nvme_namespace {scalar_t__ boundary; } ;
struct nvme_dsm_range {int /*<<< orphan*/  starting_lba; int /*<<< orphan*/  length; } ;
struct bio {int bio_cmd; int bio_offset; int bio_bcount; struct nvme_dsm_range* bio_driver2; int /*<<< orphan*/  bio_driver1; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
#define  BIO_DELETE 131 
#define  BIO_FLUSH 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NVME ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct nvme_dsm_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  htole64 (int) ; 
 struct nvme_dsm_range* malloc (int,int /*<<< orphan*/ ,int) ; 
 int nvme_get_num_segments (int,int,scalar_t__) ; 
 int /*<<< orphan*/  nvme_ns_bio_done ; 
 int nvme_ns_cmd_deallocate (struct nvme_namespace*,struct nvme_dsm_range*,int,int /*<<< orphan*/ ,struct bio*) ; 
 int nvme_ns_cmd_flush (struct nvme_namespace*,int /*<<< orphan*/ ,struct bio*) ; 
 int nvme_ns_cmd_read_bio (struct nvme_namespace*,struct bio*,int /*<<< orphan*/ ,struct bio*) ; 
 int nvme_ns_cmd_write_bio (struct nvme_namespace*,struct bio*,int /*<<< orphan*/ ,struct bio*) ; 
 int nvme_ns_get_sector_size (struct nvme_namespace*) ; 
 int nvme_ns_split_bio (struct nvme_namespace*,struct bio*,scalar_t__) ; 

int
nvme_ns_bio_process(struct nvme_namespace *ns, struct bio *bp,
	nvme_cb_fn_t cb_fn)
{
	struct nvme_dsm_range	*dsm_range;
	uint32_t		num_bios;
	int			err;

	bp->bio_driver1 = cb_fn;

	if (ns->boundary > 0 &&
	    (bp->bio_cmd == BIO_READ || bp->bio_cmd == BIO_WRITE)) {
		num_bios = nvme_get_num_segments(bp->bio_offset,
		    bp->bio_bcount, ns->boundary);
		if (num_bios > 1)
			return (nvme_ns_split_bio(ns, bp, ns->boundary));
	}

	switch (bp->bio_cmd) {
	case BIO_READ:
		err = nvme_ns_cmd_read_bio(ns, bp, nvme_ns_bio_done, bp);
		break;
	case BIO_WRITE:
		err = nvme_ns_cmd_write_bio(ns, bp, nvme_ns_bio_done, bp);
		break;
	case BIO_FLUSH:
		err = nvme_ns_cmd_flush(ns, nvme_ns_bio_done, bp);
		break;
	case BIO_DELETE:
		dsm_range =
		    malloc(sizeof(struct nvme_dsm_range), M_NVME,
		    M_ZERO | M_WAITOK);
		if (!dsm_range) {
			err = ENOMEM;
			break;
		}
		dsm_range->length =
		    htole32(bp->bio_bcount/nvme_ns_get_sector_size(ns));
		dsm_range->starting_lba =
		    htole64(bp->bio_offset/nvme_ns_get_sector_size(ns));
		bp->bio_driver2 = dsm_range;
		err = nvme_ns_cmd_deallocate(ns, dsm_range, 1,
			nvme_ns_bio_done, bp);
		if (err != 0)
			free(dsm_range, M_NVME);
		break;
	default:
		err = EIO;
		break;
	}

	return (err);
}