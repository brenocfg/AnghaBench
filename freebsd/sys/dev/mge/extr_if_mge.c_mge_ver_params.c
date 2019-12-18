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
typedef  int uint32_t ;
struct mge_softc {int mge_ver; int mge_mtu; int mge_tfut_ipg_max; int mge_rx_ipg_max; int mge_tx_arb_cfg; int mge_tx_tok_cfg; int mge_tx_tok_cnt; int mge_intr_cnt; int mge_hw_csum; } ;

/* Variables and functions */
 int MV_DEV_88F6281 ; 
 int MV_DEV_88F6282 ; 
 int MV_DEV_88F6781 ; 
 int MV_DEV_88RC8180 ; 
 int MV_DEV_DISCOVERY ; 
 int MV_DEV_FAMILY_MASK ; 
 int MV_DEV_MV78100 ; 
 int MV_DEV_MV78100_Z0 ; 
 int MV_DEV_MV78160 ; 
 int MV_DEV_MV78260 ; 
 int MV_DEV_MV78460 ; 
 int /*<<< orphan*/  soc_id (int*,int*) ; 

__attribute__((used)) static void
mge_ver_params(struct mge_softc *sc)
{
	uint32_t d, r;

	soc_id(&d, &r);
	if (d == MV_DEV_88F6281 || d == MV_DEV_88F6781 ||
	    d == MV_DEV_88F6282 ||
	    d == MV_DEV_MV78100 ||
	    d == MV_DEV_MV78100_Z0 ||
	    (d & MV_DEV_FAMILY_MASK) == MV_DEV_DISCOVERY) {
		sc->mge_ver = 2;
		sc->mge_mtu = 0x4e8;
		sc->mge_tfut_ipg_max = 0xFFFF;
		sc->mge_rx_ipg_max = 0xFFFF;
		sc->mge_tx_arb_cfg = 0xFC0000FF;
		sc->mge_tx_tok_cfg = 0xFFFF7FFF;
		sc->mge_tx_tok_cnt = 0x3FFFFFFF;
	} else {
		sc->mge_ver = 1;
		sc->mge_mtu = 0x458;
		sc->mge_tfut_ipg_max = 0x3FFF;
		sc->mge_rx_ipg_max = 0x3FFF;
		sc->mge_tx_arb_cfg = 0x000000FF;
		sc->mge_tx_tok_cfg = 0x3FFFFFFF;
		sc->mge_tx_tok_cnt = 0x3FFFFFFF;
	}
	if (d == MV_DEV_88RC8180)
		sc->mge_intr_cnt = 1;
	else
		sc->mge_intr_cnt = 2;

	if (d == MV_DEV_MV78160 || d == MV_DEV_MV78260 || d == MV_DEV_MV78460)
		sc->mge_hw_csum = 0;
	else
		sc->mge_hw_csum = 1;
}