#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kern_data_ptr; } ;
union ctl_io {TYPE_1__ scsiio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_int ;
struct ctl_lba_len_flags {int flags; scalar_t__ lba; scalar_t__ len; } ;
struct ctl_be_ramdisk_lun {int dummy; } ;
struct ctl_be_lun {scalar_t__ pblockexp; scalar_t__ blocksize; struct ctl_be_ramdisk_lun* be_lun; } ;

/* Variables and functions */
 struct ctl_lba_len_flags* ARGS (union ctl_io*) ; 
 struct ctl_be_lun* CTL_BACKEND_LUN (union ctl_io*) ; 
 int /*<<< orphan*/  GP_WRITE ; 
 int /*<<< orphan*/ * P_ANCHORED ; 
 int /*<<< orphan*/ * P_UNMAPPED ; 
 int SWS_ANCHOR ; 
 int SWS_LBDATA ; 
 int SWS_NDOB ; 
 int SWS_UNMAP ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  ctl_backend_ramdisk_delete (struct ctl_be_lun*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/ * ctl_backend_ramdisk_getpage (struct ctl_be_ramdisk_lun*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_config_write_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_data_submit_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (TYPE_1__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_space_alloc_fail (TYPE_1__*) ; 
 int /*<<< orphan*/  ctl_set_success (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scsi_ulto4b (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ctl_backend_ramdisk_ws(union ctl_io *io)
{
	struct ctl_be_lun *cbe_lun = CTL_BACKEND_LUN(io);
	struct ctl_be_ramdisk_lun *be_lun = cbe_lun->be_lun;
	struct ctl_lba_len_flags *lbalen = ARGS(io);
	uint8_t *page;
	uint64_t lba;
	u_int lbaoff, lbas;

	if (lbalen->flags & ~(SWS_LBDATA | SWS_UNMAP | SWS_ANCHOR | SWS_NDOB)) {
		ctl_set_invalid_field(&io->scsiio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ 1,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		ctl_config_write_done(io);
		return;
	}
	if (lbalen->flags & SWS_UNMAP) {
		ctl_backend_ramdisk_delete(cbe_lun, lbalen->lba, lbalen->len,
		    (lbalen->flags & SWS_ANCHOR) != 0);
		ctl_set_success(&io->scsiio);
		ctl_config_write_done(io);
		return;
	}

	for (lba = lbalen->lba, lbas = lbalen->len; lbas > 0; lba++, lbas--) {
		page = ctl_backend_ramdisk_getpage(be_lun,
		    lba >> cbe_lun->pblockexp, GP_WRITE);
		if (page == P_UNMAPPED || page == P_ANCHORED) {
			ctl_set_space_alloc_fail(&io->scsiio);
			ctl_data_submit_done(io);
			return;
		}
		lbaoff = lba & ~(UINT_MAX << cbe_lun->pblockexp);
		page += lbaoff * cbe_lun->blocksize;
		if (lbalen->flags & SWS_NDOB) {
			memset(page, 0, cbe_lun->blocksize);
		} else {
			memcpy(page, io->scsiio.kern_data_ptr,
			    cbe_lun->blocksize);
		}
		if (lbalen->flags & SWS_LBDATA)
			scsi_ulto4b(lba, page);
	}
	ctl_set_success(&io->scsiio);
	ctl_config_write_done(io);
}