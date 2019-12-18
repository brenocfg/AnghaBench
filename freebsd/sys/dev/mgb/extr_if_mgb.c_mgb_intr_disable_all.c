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
struct mgb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGB_DMAC_INTR_ENBL_CLR ; 
 int /*<<< orphan*/  MGB_DMAC_INTR_STS ; 
 int /*<<< orphan*/  MGB_INTR_ENBL_CLR ; 
 int /*<<< orphan*/  MGB_INTR_STS ; 
 int /*<<< orphan*/  MGB_INTR_VEC_ENBL_CLR ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mgb_intr_disable_all(if_ctx_t ctx)
{
	struct mgb_softc *sc;

	sc = iflib_get_softc(ctx);
	CSR_WRITE_REG(sc, MGB_INTR_ENBL_CLR, UINT32_MAX);
	CSR_WRITE_REG(sc, MGB_INTR_VEC_ENBL_CLR, UINT32_MAX);
	CSR_WRITE_REG(sc, MGB_INTR_STS, UINT32_MAX);

	CSR_WRITE_REG(sc, MGB_DMAC_INTR_ENBL_CLR, UINT32_MAX);
	CSR_WRITE_REG(sc, MGB_DMAC_INTR_STS, UINT32_MAX);
}