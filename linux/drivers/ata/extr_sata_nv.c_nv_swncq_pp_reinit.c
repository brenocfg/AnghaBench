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
struct defer_queue {scalar_t__ defer_bits; scalar_t__ tail; scalar_t__ head; } ;
struct nv_swncq_port_priv {int /*<<< orphan*/  last_issue_tag; scalar_t__ qc_active; struct defer_queue defer_queue; } ;
struct ata_port {struct nv_swncq_port_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_TAG_POISON ; 
 int /*<<< orphan*/  nv_swncq_fis_reinit (struct ata_port*) ; 

__attribute__((used)) static void nv_swncq_pp_reinit(struct ata_port *ap)
{
	struct nv_swncq_port_priv *pp = ap->private_data;
	struct defer_queue *dq = &pp->defer_queue;

	dq->head = 0;
	dq->tail = 0;
	dq->defer_bits = 0;
	pp->qc_active = 0;
	pp->last_issue_tag = ATA_TAG_POISON;
	nv_swncq_fis_reinit(ap);
}