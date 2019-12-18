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
typedef  int u8 ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void atapi_fixup_inquiry(struct scsi_cmnd *cmd)
{
	u8 buf[4];

	sg_copy_to_buffer(scsi_sglist(cmd), scsi_sg_count(cmd), buf, 4);
	if (buf[2] == 0) {
		buf[2] = 0x5;
		buf[3] = 0x32;
	}
	sg_copy_from_buffer(scsi_sglist(cmd), scsi_sg_count(cmd), buf, 4);
}