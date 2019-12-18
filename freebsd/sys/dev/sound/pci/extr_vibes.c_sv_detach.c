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
struct sc_info {int /*<<< orphan*/  dmac_reg; int /*<<< orphan*/  dmac_rid; int /*<<< orphan*/  dmac_type; int /*<<< orphan*/  dmaa_reg; int /*<<< orphan*/  dmaa_rid; int /*<<< orphan*/  dmaa_type; int /*<<< orphan*/  enh_reg; int /*<<< orphan*/  enh_rid; int /*<<< orphan*/  enh_type; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqid; int /*<<< orphan*/  ih; int /*<<< orphan*/  parent_dmat; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sc_info*,int /*<<< orphan*/ ) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_mix_mute_all (struct sc_info*) ; 
 int /*<<< orphan*/  sv_power (struct sc_info*,int) ; 

__attribute__((used)) static int
sv_detach(device_t dev) {
	struct sc_info	*sc;
	int		r;

	r = pcm_unregister(dev);
	if (r) return r;

	sc = pcm_getdevinfo(dev);
	sv_mix_mute_all(sc);
	sv_power(sc, 3);

	bus_dma_tag_destroy(sc->parent_dmat);
	bus_teardown_intr(dev, sc->irq, sc->ih);
	bus_release_resource(dev, SYS_RES_IRQ, sc->irqid, sc->irq);
	bus_release_resource(dev, sc->enh_type, sc->enh_rid, sc->enh_reg);
	bus_release_resource(dev, sc->dmaa_type, sc->dmaa_rid, sc->dmaa_reg);
	bus_release_resource(dev, sc->dmac_type, sc->dmac_rid, sc->dmac_reg);

	free(sc, M_DEVBUF);

	return 0;
}