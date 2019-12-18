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
struct nv_swncq_port_priv {int last_issue_tag; int dhfis_bits; int dmafis_bits; int qc_active; int /*<<< orphan*/  sactive_block; } ;
struct ata_queued_cmd {int hw_tag; int /*<<< orphan*/  tf; } ;
struct ata_port {TYPE_1__* ops; struct nv_swncq_port_priv* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sff_exec_command ) (struct ata_port*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* sff_tf_load ) (struct ata_port*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int nv_swncq_issue_atacmd(struct ata_port *ap,
					  struct ata_queued_cmd *qc)
{
	struct nv_swncq_port_priv *pp = ap->private_data;

	if (qc == NULL)
		return 0;

	DPRINTK("Enter\n");

	writel((1 << qc->hw_tag), pp->sactive_block);
	pp->last_issue_tag = qc->hw_tag;
	pp->dhfis_bits &= ~(1 << qc->hw_tag);
	pp->dmafis_bits &= ~(1 << qc->hw_tag);
	pp->qc_active |= (0x1 << qc->hw_tag);

	ap->ops->sff_tf_load(ap, &qc->tf);	 /* load tf registers */
	ap->ops->sff_exec_command(ap, &qc->tf);

	DPRINTK("Issued tag %u\n", qc->hw_tag);

	return 0;
}