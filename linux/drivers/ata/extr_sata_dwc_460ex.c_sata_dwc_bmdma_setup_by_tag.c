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
typedef  int /*<<< orphan*/  u8 ;
struct ata_queued_cmd {int /*<<< orphan*/  tf; int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SATA_DWC_CMD_ISSUED_PEND ; 
 int /*<<< orphan*/  sata_dwc_exec_command_by_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sata_dwc_bmdma_setup_by_tag(struct ata_queued_cmd *qc, u8 tag)
{
	sata_dwc_exec_command_by_tag(qc->ap, &qc->tf, tag,
				     SATA_DWC_CMD_ISSUED_PEND);
}