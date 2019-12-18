#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* cdb; } ;
union ctl_io {TYPE_1__ scsiio; } ;
struct scsi_start_stop_unit {int how; } ;
struct ctl_be_lun {int dummy; } ;

/* Variables and functions */
 struct ctl_be_lun* CTL_BACKEND_LUN (union ctl_io*) ; 
 int CTL_RETVAL_COMPLETE ; 
#define  PREVENT_ALLOW 134 
 int SSS_LOEJ ; 
 int SSS_PC_MASK ; 
 int SSS_START ; 
#define  START_STOP_UNIT 133 
#define  SYNCHRONIZE_CACHE 132 
#define  SYNCHRONIZE_CACHE_16 131 
#define  UNMAP 130 
#define  WRITE_SAME_10 129 
#define  WRITE_SAME_16 128 
 int /*<<< orphan*/  ctl_backend_ramdisk_unmap (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_backend_ramdisk_ws (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_config_write_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_lun_ejected (struct ctl_be_lun*) ; 
 int /*<<< orphan*/  ctl_lun_has_media (struct ctl_be_lun*) ; 
 int /*<<< orphan*/  ctl_set_invalid_opcode (TYPE_1__*) ; 
 int /*<<< orphan*/  ctl_set_success (TYPE_1__*) ; 
 int /*<<< orphan*/  ctl_start_lun (struct ctl_be_lun*) ; 
 int /*<<< orphan*/  ctl_stop_lun (struct ctl_be_lun*) ; 

__attribute__((used)) static int
ctl_backend_ramdisk_config_write(union ctl_io *io)
{
	struct ctl_be_lun *cbe_lun = CTL_BACKEND_LUN(io);
	int retval = 0;

	switch (io->scsiio.cdb[0]) {
	case SYNCHRONIZE_CACHE:
	case SYNCHRONIZE_CACHE_16:
		/* We have no cache to flush. */
		ctl_set_success(&io->scsiio);
		ctl_config_write_done(io);
		break;
	case START_STOP_UNIT: {
		struct scsi_start_stop_unit *cdb;

		cdb = (struct scsi_start_stop_unit *)io->scsiio.cdb;
		if ((cdb->how & SSS_PC_MASK) != 0) {
			ctl_set_success(&io->scsiio);
			ctl_config_write_done(io);
			break;
		}
		if (cdb->how & SSS_START) {
			if (cdb->how & SSS_LOEJ)
				ctl_lun_has_media(cbe_lun);
			ctl_start_lun(cbe_lun);
		} else {
			ctl_stop_lun(cbe_lun);
			if (cdb->how & SSS_LOEJ)
				ctl_lun_ejected(cbe_lun);
		}
		ctl_set_success(&io->scsiio);
		ctl_config_write_done(io);
		break;
	}
	case PREVENT_ALLOW:
		ctl_set_success(&io->scsiio);
		ctl_config_write_done(io);
		break;
	case WRITE_SAME_10:
	case WRITE_SAME_16:
		ctl_backend_ramdisk_ws(io);
		break;
	case UNMAP:
		ctl_backend_ramdisk_unmap(io);
		break;
	default:
		ctl_set_invalid_opcode(&io->scsiio);
		ctl_config_write_done(io);
		retval = CTL_RETVAL_COMPLETE;
		break;
	}

	return (retval);
}