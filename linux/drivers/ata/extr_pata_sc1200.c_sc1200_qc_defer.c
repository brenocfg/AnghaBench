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
struct ata_queued_cmd {TYPE_1__* ap; } ;
struct ata_port {scalar_t__ qc_active; } ;
struct ata_host {struct ata_port** ports; } ;
struct TYPE_2__ {int port_no; struct ata_host* host; } ;

/* Variables and functions */
 int ATA_DEFER_PORT ; 
 int ata_std_qc_defer (struct ata_queued_cmd*) ; 

__attribute__((used)) static int sc1200_qc_defer(struct ata_queued_cmd *qc)
{
	struct ata_host *host = qc->ap->host;
	struct ata_port *alt = host->ports[1 ^ qc->ap->port_no];
	int rc;

	/* First apply the usual rules */
	rc = ata_std_qc_defer(qc);
	if (rc != 0)
		return rc;

	/* Now apply serialization rules. Only allow a command if the
	   other channel state machine is idle */
	if (alt && alt->qc_active)
		return	ATA_DEFER_PORT;
	return 0;
}