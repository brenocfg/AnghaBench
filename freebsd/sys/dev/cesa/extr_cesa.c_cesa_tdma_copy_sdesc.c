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
struct cesa_softc {int /*<<< orphan*/  sc_sram_base_pa; } ;
struct cesa_sa_hdesc {int dummy; } ;
struct cesa_sa_desc {int /*<<< orphan*/  csd_cshd_paddr; } ;

/* Variables and functions */
 struct cesa_tdma_desc* cesa_tdma_copy (struct cesa_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct cesa_tdma_desc *
cesa_tdma_copy_sdesc(struct cesa_softc *sc, struct cesa_sa_desc *csd)
{

	return (cesa_tdma_copy(sc, sc->sc_sram_base_pa, csd->csd_cshd_paddr,
	    sizeof(struct cesa_sa_hdesc)));
}