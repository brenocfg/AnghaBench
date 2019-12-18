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
struct octeon_cf_port {scalar_t__ dma_finished; } ;
struct ata_queued_cmd {int /*<<< orphan*/  tf; int /*<<< orphan*/  sg; int /*<<< orphan*/  cursg; struct ata_port* ap; } ;
struct ata_port {TYPE_1__* ops; struct octeon_cf_port* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sff_exec_command ) (struct ata_port*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void octeon_cf_dma_setup(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct octeon_cf_port *cf_port;

	cf_port = ap->private_data;
	DPRINTK("ENTER\n");
	/* issue r/w command */
	qc->cursg = qc->sg;
	cf_port->dma_finished = 0;
	ap->ops->sff_exec_command(ap, &qc->tf);
	DPRINTK("EXIT\n");
}