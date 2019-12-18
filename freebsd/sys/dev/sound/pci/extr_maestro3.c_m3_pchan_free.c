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
struct sc_pchinfo {int /*<<< orphan*/  dac_idx; struct sc_info* parent; } ;
struct sc_info {int pch_cnt; int rch_cnt; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE ; 
 int KDATA_DMA_XFER0 ; 
 int KDATA_INSTANCE0_MINISRC ; 
 int KDATA_MIXER_XFER0 ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  m3_wr_assp_data (struct sc_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
m3_pchan_free(kobj_t kobj, void *chdata)
{
	struct sc_pchinfo *ch = chdata;
	struct sc_info *sc = ch->parent;

	M3_LOCK(sc);
        M3_DEBUG(CHANGE, ("m3_pchan_free(dac=%d)\n", ch->dac_idx));

	/*
	 * should remove this exact instance from the packed lists, but all
	 * are released at once (and in a stopped state) so this is ok.
	 */
	m3_wr_assp_data(sc, KDATA_INSTANCE0_MINISRC +
			(sc->pch_cnt - 1) + sc->rch_cnt, 0);
	m3_wr_assp_data(sc, KDATA_DMA_XFER0 +
			(sc->pch_cnt - 1) + sc->rch_cnt, 0);
	m3_wr_assp_data(sc, KDATA_MIXER_XFER0 + (sc->pch_cnt-1), 0);
	sc->pch_cnt--;
	M3_UNLOCK(sc);

	return (0);
}