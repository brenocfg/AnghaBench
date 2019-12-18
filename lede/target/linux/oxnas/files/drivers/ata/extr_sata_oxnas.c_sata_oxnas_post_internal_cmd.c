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
struct ata_queued_cmd {int flags; TYPE_1__* ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ATA_QCFLAG_FAILED ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  sata_oxnas_cleanup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sata_oxnas_post_internal_cmd(struct ata_queued_cmd *qc)
{
	DPRINTK("ENTER\n");
	/* If the core is busy here, make it idle */
	if (qc->flags & ATA_QCFLAG_FAILED)
		sata_oxnas_cleanup(qc->ap->host);
}