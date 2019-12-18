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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct scsi_rw_6 {int /*<<< orphan*/  addr; } ;
struct scsi_rw_16 {int /*<<< orphan*/  addr; } ;
struct scsi_rw_12 {int /*<<< orphan*/  addr; } ;
struct scsi_rw_10 {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  READ_10 135 
#define  READ_12 134 
#define  READ_16 133 
#define  READ_6 132 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 int /*<<< orphan*/  scsi_3btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_8btou64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int64_t 
aac_eval_blockno(u_int8_t *cmdp) 
{
	u_int64_t blockno;

	switch (cmdp[0]) {
	case READ_6:
	case WRITE_6:
		blockno = scsi_3btoul(((struct scsi_rw_6 *)cmdp)->addr);	
		break;
	case READ_10:
	case WRITE_10:
		blockno = scsi_4btoul(((struct scsi_rw_10 *)cmdp)->addr);	
		break;
	case READ_12:
	case WRITE_12:
		blockno = scsi_4btoul(((struct scsi_rw_12 *)cmdp)->addr);	
		break;
	case READ_16:
	case WRITE_16:
		blockno = scsi_8btou64(((struct scsi_rw_16 *)cmdp)->addr);	
		break;
	default:
		blockno = 0;
		break;
	}
	return(blockno);
}