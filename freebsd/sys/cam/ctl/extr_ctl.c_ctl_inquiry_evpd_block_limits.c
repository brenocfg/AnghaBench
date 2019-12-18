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
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  int uint64_t ;
struct scsi_vpd_block_limits {int device; int max_cmp_write_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_write_same_length; int /*<<< orphan*/  max_atomic_boundary_size; int /*<<< orphan*/  max_atomic_transfer_length_with_atomic_boundary; int /*<<< orphan*/  atomic_transfer_length_granularity; int /*<<< orphan*/  atomic_alignment; int /*<<< orphan*/  max_atomic_transfer_length; int /*<<< orphan*/  unmap_grain_align; int /*<<< orphan*/  opt_unmap_grain; int /*<<< orphan*/  max_unmap_blk_cnt; int /*<<< orphan*/  max_unmap_lba_cnt; int /*<<< orphan*/  opt_txfer_len; int /*<<< orphan*/  max_txfer_len; int /*<<< orphan*/  page_length; int /*<<< orphan*/  page_code; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; scalar_t__ kern_data_ptr; } ;
struct ctl_lun {TYPE_1__* be_lun; } ;
struct TYPE_3__ {int lun_type; int opttxferlen; int flags; int ublockexp; int ublockoff; int atomicblock; int maxlba; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_LUN_FLAG_UNMAP ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SID_QUAL_LU_CONNECTED ; 
 int SID_QUAL_LU_OFFLINE ; 
 int /*<<< orphan*/  SVPD_BLOCK_LIMITS ; 
 int /*<<< orphan*/  SVPD_BL_WSNZ ; 
 int T_DIRECT ; 
 int UINT64_MAX ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_expand_number (char const*,int*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 char* dnvlist_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  scsi_u64to8b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_inquiry_evpd_block_limits(struct ctl_scsiio *ctsio, int alloc_len)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_vpd_block_limits *bl_ptr;
	const char *val;
	uint64_t ival;

	ctsio->kern_data_ptr = malloc(sizeof(*bl_ptr), M_CTL, M_WAITOK | M_ZERO);
	bl_ptr = (struct scsi_vpd_block_limits *)ctsio->kern_data_ptr;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_data_len = min(sizeof(*bl_ptr), alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	/*
	 * The control device is always connected.  The disk device, on the
	 * other hand, may not be online all the time.  Need to change this
	 * to figure out whether the disk device is actually online or not.
	 */
	if (lun != NULL)
		bl_ptr->device = (SID_QUAL_LU_CONNECTED << 5) |
				  lun->be_lun->lun_type;
	else
		bl_ptr->device = (SID_QUAL_LU_OFFLINE << 5) | T_DIRECT;

	bl_ptr->page_code = SVPD_BLOCK_LIMITS;
	scsi_ulto2b(sizeof(*bl_ptr) - 4, bl_ptr->page_length);
	bl_ptr->max_cmp_write_len = 0xff;
	scsi_ulto4b(0xffffffff, bl_ptr->max_txfer_len);
	if (lun != NULL) {
		scsi_ulto4b(lun->be_lun->opttxferlen, bl_ptr->opt_txfer_len);
		if (lun->be_lun->flags & CTL_LUN_FLAG_UNMAP) {
			ival = 0xffffffff;
			val = dnvlist_get_string(lun->be_lun->options,
			    "unmap_max_lba", NULL);
			if (val != NULL)
				ctl_expand_number(val, &ival);
			scsi_ulto4b(ival, bl_ptr->max_unmap_lba_cnt);
			ival = 0xffffffff;
			val = dnvlist_get_string(lun->be_lun->options,
			    "unmap_max_descr", NULL);
			if (val != NULL)
				ctl_expand_number(val, &ival);
			scsi_ulto4b(ival, bl_ptr->max_unmap_blk_cnt);
			if (lun->be_lun->ublockexp != 0) {
				scsi_ulto4b((1 << lun->be_lun->ublockexp),
				    bl_ptr->opt_unmap_grain);
				scsi_ulto4b(0x80000000 | lun->be_lun->ublockoff,
				    bl_ptr->unmap_grain_align);
			}
		}
		scsi_ulto4b(lun->be_lun->atomicblock,
		    bl_ptr->max_atomic_transfer_length);
		scsi_ulto4b(0, bl_ptr->atomic_alignment);
		scsi_ulto4b(0, bl_ptr->atomic_transfer_length_granularity);
		scsi_ulto4b(0, bl_ptr->max_atomic_transfer_length_with_atomic_boundary);
		scsi_ulto4b(0, bl_ptr->max_atomic_boundary_size);
		ival = UINT64_MAX;
		val = dnvlist_get_string(lun->be_lun->options,
		    "write_same_max_lba", NULL);
		if (val != NULL)
			ctl_expand_number(val, &ival);
		scsi_u64to8b(ival, bl_ptr->max_write_same_length);
		if (lun->be_lun->maxlba + 1 > ival)
			bl_ptr->flags |= SVPD_BL_WSNZ;
	}

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}