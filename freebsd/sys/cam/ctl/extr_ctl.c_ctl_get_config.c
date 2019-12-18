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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct scsi_get_config_header {int* current_profile; int* data_length; } ;
struct scsi_get_config_feature {int* feature_code; int flags; int add_length; int* feature_data; } ;
struct scsi_get_config {int rt; int* starting_feature; int* length; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_data_ptr; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ cdb; } ;
struct ctl_lun {int flags; TYPE_1__* be_lun; } ;
struct TYPE_3__ {int blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_LUN_NO_MEDIA ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SGC_F_CURRENT ; 
 int SGC_F_PERSISTENT ; 
 int SGC_RT_CURRENT ; 
 int SGC_RT_MASK ; 
 int SGC_RT_SPECIFIC ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int scsi_2btoul (int*) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int*) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int*) ; 

int
ctl_get_config(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_get_config_header *hdr;
	struct scsi_get_config_feature *feature;
	struct scsi_get_config *cdb;
	uint32_t alloc_len, data_len;
	int rt, starting;

	cdb = (struct scsi_get_config *)ctsio->cdb;
	rt = (cdb->rt & SGC_RT_MASK);
	starting = scsi_2btoul(cdb->starting_feature);
	alloc_len = scsi_2btoul(cdb->length);

	data_len = sizeof(struct scsi_get_config_header) +
	    sizeof(struct scsi_get_config_feature) + 8 +
	    sizeof(struct scsi_get_config_feature) + 8 +
	    sizeof(struct scsi_get_config_feature) + 4 +
	    sizeof(struct scsi_get_config_feature) + 4 +
	    sizeof(struct scsi_get_config_feature) + 8 +
	    sizeof(struct scsi_get_config_feature) +
	    sizeof(struct scsi_get_config_feature) + 4 +
	    sizeof(struct scsi_get_config_feature) + 4 +
	    sizeof(struct scsi_get_config_feature) + 4 +
	    sizeof(struct scsi_get_config_feature) + 4 +
	    sizeof(struct scsi_get_config_feature) + 4 +
	    sizeof(struct scsi_get_config_feature) + 4;
	ctsio->kern_data_ptr = malloc(data_len, M_CTL, M_WAITOK | M_ZERO);
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;

	hdr = (struct scsi_get_config_header *)ctsio->kern_data_ptr;
	if (lun->flags & CTL_LUN_NO_MEDIA)
		scsi_ulto2b(0x0000, hdr->current_profile);
	else
		scsi_ulto2b(0x0010, hdr->current_profile);
	feature = (struct scsi_get_config_feature *)(hdr + 1);

	if (starting > 0x003b)
		goto done;
	if (starting > 0x003a)
		goto f3b;
	if (starting > 0x002b)
		goto f3a;
	if (starting > 0x002a)
		goto f2b;
	if (starting > 0x001f)
		goto f2a;
	if (starting > 0x001e)
		goto f1f;
	if (starting > 0x001d)
		goto f1e;
	if (starting > 0x0010)
		goto f1d;
	if (starting > 0x0003)
		goto f10;
	if (starting > 0x0002)
		goto f3;
	if (starting > 0x0001)
		goto f2;
	if (starting > 0x0000)
		goto f1;

	/* Profile List */
	scsi_ulto2b(0x0000, feature->feature_code);
	feature->flags = SGC_F_PERSISTENT | SGC_F_CURRENT;
	feature->add_length = 8;
	scsi_ulto2b(0x0008, &feature->feature_data[0]);	/* CD-ROM */
	feature->feature_data[2] = 0x00;
	scsi_ulto2b(0x0010, &feature->feature_data[4]);	/* DVD-ROM */
	feature->feature_data[6] = 0x01;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f1:	/* Core */
	scsi_ulto2b(0x0001, feature->feature_code);
	feature->flags = 0x08 | SGC_F_PERSISTENT | SGC_F_CURRENT;
	feature->add_length = 8;
	scsi_ulto4b(0x00000000, &feature->feature_data[0]);
	feature->feature_data[4] = 0x03;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f2:	/* Morphing */
	scsi_ulto2b(0x0002, feature->feature_code);
	feature->flags = 0x04 | SGC_F_PERSISTENT | SGC_F_CURRENT;
	feature->add_length = 4;
	feature->feature_data[0] = 0x02;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f3:	/* Removable Medium */
	scsi_ulto2b(0x0003, feature->feature_code);
	feature->flags = 0x04 | SGC_F_PERSISTENT | SGC_F_CURRENT;
	feature->add_length = 4;
	feature->feature_data[0] = 0x39;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

	if (rt == SGC_RT_CURRENT && (lun->flags & CTL_LUN_NO_MEDIA))
		goto done;

f10:	/* Random Read */
	scsi_ulto2b(0x0010, feature->feature_code);
	feature->flags = 0x00;
	if ((lun->flags & CTL_LUN_NO_MEDIA) == 0)
		feature->flags |= SGC_F_CURRENT;
	feature->add_length = 8;
	scsi_ulto4b(lun->be_lun->blocksize, &feature->feature_data[0]);
	scsi_ulto2b(1, &feature->feature_data[4]);
	feature->feature_data[6] = 0x00;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f1d:	/* Multi-Read */
	scsi_ulto2b(0x001D, feature->feature_code);
	feature->flags = 0x00;
	if ((lun->flags & CTL_LUN_NO_MEDIA) == 0)
		feature->flags |= SGC_F_CURRENT;
	feature->add_length = 0;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f1e:	/* CD Read */
	scsi_ulto2b(0x001E, feature->feature_code);
	feature->flags = 0x00;
	if ((lun->flags & CTL_LUN_NO_MEDIA) == 0)
		feature->flags |= SGC_F_CURRENT;
	feature->add_length = 4;
	feature->feature_data[0] = 0x00;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f1f:	/* DVD Read */
	scsi_ulto2b(0x001F, feature->feature_code);
	feature->flags = 0x08;
	if ((lun->flags & CTL_LUN_NO_MEDIA) == 0)
		feature->flags |= SGC_F_CURRENT;
	feature->add_length = 4;
	feature->feature_data[0] = 0x01;
	feature->feature_data[2] = 0x03;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f2a:	/* DVD+RW */
	scsi_ulto2b(0x002A, feature->feature_code);
	feature->flags = 0x04;
	if ((lun->flags & CTL_LUN_NO_MEDIA) == 0)
		feature->flags |= SGC_F_CURRENT;
	feature->add_length = 4;
	feature->feature_data[0] = 0x00;
	feature->feature_data[1] = 0x00;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f2b:	/* DVD+R */
	scsi_ulto2b(0x002B, feature->feature_code);
	feature->flags = 0x00;
	if ((lun->flags & CTL_LUN_NO_MEDIA) == 0)
		feature->flags |= SGC_F_CURRENT;
	feature->add_length = 4;
	feature->feature_data[0] = 0x00;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f3a:	/* DVD+RW Dual Layer */
	scsi_ulto2b(0x003A, feature->feature_code);
	feature->flags = 0x00;
	if ((lun->flags & CTL_LUN_NO_MEDIA) == 0)
		feature->flags |= SGC_F_CURRENT;
	feature->add_length = 4;
	feature->feature_data[0] = 0x00;
	feature->feature_data[1] = 0x00;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

f3b:	/* DVD+R Dual Layer */
	scsi_ulto2b(0x003B, feature->feature_code);
	feature->flags = 0x00;
	if ((lun->flags & CTL_LUN_NO_MEDIA) == 0)
		feature->flags |= SGC_F_CURRENT;
	feature->add_length = 4;
	feature->feature_data[0] = 0x00;
	feature = (struct scsi_get_config_feature *)
	    &feature->feature_data[feature->add_length];

done:
	data_len = (uint8_t *)feature - (uint8_t *)hdr;
	if (rt == SGC_RT_SPECIFIC && data_len > 4) {
		feature = (struct scsi_get_config_feature *)(hdr + 1);
		if (scsi_2btoul(feature->feature_code) == starting)
			feature = (struct scsi_get_config_feature *)
			    &feature->feature_data[feature->add_length];
		data_len = (uint8_t *)feature - (uint8_t *)hdr;
	}
	scsi_ulto4b(data_len - 4, hdr->data_length);
	ctsio->kern_data_len = min(data_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}