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
struct cesa_tdma_desc {int dummy; } ;
struct cesa_softc {scalar_t__ sc_sram_base_pa; } ;
struct cesa_sa_hdesc {int dummy; } ;
struct cesa_sa_data {int dummy; } ;
struct cesa_request {int /*<<< orphan*/  cr_csd_paddr; } ;

/* Variables and functions */
 struct cesa_tdma_desc* cesa_tdma_copy (struct cesa_softc*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct cesa_tdma_desc *
cesa_tdma_copyin_sa_data(struct cesa_softc *sc, struct cesa_request *cr)
{

	return (cesa_tdma_copy(sc, sc->sc_sram_base_pa +
	    sizeof(struct cesa_sa_hdesc), cr->cr_csd_paddr,
	    sizeof(struct cesa_sa_data)));
}