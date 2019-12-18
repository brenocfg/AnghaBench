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
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {scalar_t__ func_code; int /*<<< orphan*/  path; } ;
union ccb {TYPE_2__ ataio; TYPE_1__ ccb_h; } ;
struct ata_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  cdb_str ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_CDB ; 
 scalar_t__ XPT_ATA_IO ; 
 int /*<<< orphan*/  ata_cmd_string (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ata_op_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ata_proto_debug_out(union ccb *ccb)
{
	char cdb_str[(sizeof(struct ata_cmd) * 3) + 1];

	if (ccb->ccb_h.func_code != XPT_ATA_IO)
		return;

	CAM_DEBUG(ccb->ccb_h.path,
	    CAM_DEBUG_CDB,("%s. ACB: %s\n", ata_op_string(&ccb->ataio.cmd),
		ata_cmd_string(&ccb->ataio.cmd, cdb_str, sizeof(cdb_str))));
}