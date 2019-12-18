#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_rdmasniff {int /*<<< orphan*/  oneshot_buffer; int /*<<< orphan*/  context; int /*<<< orphan*/  channel; int /*<<< orphan*/  pd; int /*<<< orphan*/  cq; int /*<<< orphan*/  qp; int /*<<< orphan*/  flow; int /*<<< orphan*/  mr; } ;
struct TYPE_4__ {struct pcap_rdmasniff* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_close_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_dereg_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_comp_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_flow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_1__*) ; 

__attribute__((used)) static void
rdmasniff_cleanup(pcap_t *handle)
{
	struct pcap_rdmasniff *priv = handle->priv;

	ibv_dereg_mr(priv->mr);
	ibv_destroy_flow(priv->flow);
	ibv_destroy_qp(priv->qp);
	ibv_destroy_cq(priv->cq);
	ibv_dealloc_pd(priv->pd);
	ibv_destroy_comp_channel(priv->channel);
	ibv_close_device(priv->context);
	free(priv->oneshot_buffer);

	pcap_cleanup_live_common(handle);
}