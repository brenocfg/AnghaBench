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
typedef  int /*<<< orphan*/  u_int16_t ;
struct agg_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  buf_dmat; int /*<<< orphan*/  stat_dmat; int /*<<< orphan*/  stat_map; int /*<<< orphan*/  stat; int /*<<< orphan*/  reg; int /*<<< orphan*/  regid; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; scalar_t__ active; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGG_RD (struct agg_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AGG_WR (struct agg_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PCI_POWERSTATE_D3 ; 
 int /*<<< orphan*/  PORT_HOSTINT_CTRL ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  agg_lock (struct agg_info*) ; 
 int /*<<< orphan*/  agg_power (struct agg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_unlock (struct agg_info*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct agg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 struct agg_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agg_detach(device_t dev)
{
	struct agg_info	*ess = pcm_getdevinfo(dev);
	int r;
	u_int16_t icr;

	icr = AGG_RD(ess, PORT_HOSTINT_CTRL, 2);
	AGG_WR(ess, PORT_HOSTINT_CTRL, 0, 2);

	agg_lock(ess);
	if (ess->active) {
		AGG_WR(ess, PORT_HOSTINT_CTRL, icr, 2);
		agg_unlock(ess);
		return EBUSY;
	}
	agg_unlock(ess);

	r = pcm_unregister(dev);
	if (r) {
		AGG_WR(ess, PORT_HOSTINT_CTRL, icr, 2);
		return r;
	}

	agg_lock(ess);
	agg_power(ess, PCI_POWERSTATE_D3);
	agg_unlock(ess);

	bus_teardown_intr(dev, ess->irq, ess->ih);
	bus_release_resource(dev, SYS_RES_IRQ, ess->irqid, ess->irq);
	bus_release_resource(dev, SYS_RES_IOPORT, ess->regid, ess->reg);
	dma_free(ess->stat_dmat, ess->stat, ess->stat_map);
	bus_dma_tag_destroy(ess->stat_dmat);
	bus_dma_tag_destroy(ess->buf_dmat);
	mtx_destroy(&ess->lock);
	free(ess, M_DEVBUF);
	return 0;
}