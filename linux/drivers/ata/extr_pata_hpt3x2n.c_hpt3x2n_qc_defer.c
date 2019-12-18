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
struct TYPE_3__ {int flags; } ;
struct ata_queued_cmd {TYPE_1__ tf; struct ata_port* ap; } ;
struct ata_port {int port_no; scalar_t__ qc_active; TYPE_2__* host; } ;
struct TYPE_4__ {scalar_t__ private_data; struct ata_port** ports; } ;

/* Variables and functions */
 int ATA_DEFER_PORT ; 
 int ATA_TFLAG_WRITE ; 
 int USE_DPLL ; 
 int ata_std_qc_defer (struct ata_queued_cmd*) ; 
 int hpt3x2n_use_dpll (struct ata_port*,int) ; 

__attribute__((used)) static int hpt3x2n_qc_defer(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_port *alt = ap->host->ports[ap->port_no ^ 1];
	int rc, flags = (long)ap->host->private_data;
	int dpll = hpt3x2n_use_dpll(ap, qc->tf.flags & ATA_TFLAG_WRITE);

	/* First apply the usual rules */
	rc = ata_std_qc_defer(qc);
	if (rc != 0)
		return rc;

	if ((flags & USE_DPLL) != dpll && alt->qc_active)
		return ATA_DEFER_PORT;
	return 0;
}