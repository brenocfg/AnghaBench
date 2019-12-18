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
struct pata_macio_priv {int aapl_bus_id; scalar_t__ mediabay; int /*<<< orphan*/  node; void* timings; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  controller_heathrow ; 
 int /*<<< orphan*/  controller_k2_ata6 ; 
 int /*<<< orphan*/  controller_kl_ata3 ; 
 int /*<<< orphan*/  controller_kl_ata4 ; 
 int /*<<< orphan*/  controller_ohare ; 
 int /*<<< orphan*/  controller_sh_ata6 ; 
 int /*<<< orphan*/  controller_un_ata6 ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_node_name_eq (int /*<<< orphan*/ ,char*) ; 
 void* pata_macio_heathrow_timings ; 
 void* pata_macio_kauai_timings ; 
 void* pata_macio_kl33_timings ; 
 void* pata_macio_kl66_timings ; 
 void* pata_macio_ohare_timings ; 
 void* pata_macio_shasta_timings ; 

__attribute__((used)) static void pata_macio_invariants(struct pata_macio_priv *priv)
{
	const int *bidp;

	/* Identify the type of controller */
	if (of_device_is_compatible(priv->node, "shasta-ata")) {
		priv->kind = controller_sh_ata6;
	        priv->timings = pata_macio_shasta_timings;
	} else if (of_device_is_compatible(priv->node, "kauai-ata")) {
		priv->kind = controller_un_ata6;
	        priv->timings = pata_macio_kauai_timings;
	} else if (of_device_is_compatible(priv->node, "K2-UATA")) {
		priv->kind = controller_k2_ata6;
	        priv->timings = pata_macio_kauai_timings;
	} else if (of_device_is_compatible(priv->node, "keylargo-ata")) {
		if (of_node_name_eq(priv->node, "ata-4")) {
			priv->kind = controller_kl_ata4;
			priv->timings = pata_macio_kl66_timings;
		} else {
			priv->kind = controller_kl_ata3;
			priv->timings = pata_macio_kl33_timings;
		}
	} else if (of_device_is_compatible(priv->node, "heathrow-ata")) {
		priv->kind = controller_heathrow;
		priv->timings = pata_macio_heathrow_timings;
	} else {
		priv->kind = controller_ohare;
		priv->timings = pata_macio_ohare_timings;
	}

	/* XXX FIXME --- setup priv->mediabay here */

	/* Get Apple bus ID (for clock and ASIC control) */
	bidp = of_get_property(priv->node, "AAPL,bus-id", NULL);
	priv->aapl_bus_id =  bidp ? *bidp : 0;

	/* Fixup missing Apple bus ID in case of media-bay */
	if (priv->mediabay && bidp == 0)
		priv->aapl_bus_id = 1;
}