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
struct sc_rchinfo {int /*<<< orphan*/  adc_idx; struct sc_info* parent; } ;
struct sc_info {int rch_cnt; int pch_cnt; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE ; 
 int KDATA_ADC1_XFER0 ; 
 int KDATA_DMA_XFER0 ; 
 int KDATA_INSTANCE0_MINISRC ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  m3_wr_assp_data (struct sc_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
m3_rchan_free(kobj_t kobj, void *chdata)
{
	struct sc_rchinfo *ch = chdata;
	struct sc_info *sc = ch->parent;

	M3_LOCK(sc);
        M3_DEBUG(CHANGE, ("m3_rchan_free(adc=%d)\n", ch->adc_idx));

	/*
	 * should remove this exact instance from the packed lists, but all
	 * are released at once (and in a stopped state) so this is ok.
	 */
	m3_wr_assp_data(sc, KDATA_INSTANCE0_MINISRC +
			(sc->rch_cnt - 1) + sc->pch_cnt, 0);
	m3_wr_assp_data(sc, KDATA_DMA_XFER0 +
			(sc->rch_cnt - 1) + sc->pch_cnt, 0);
	m3_wr_assp_data(sc, KDATA_ADC1_XFER0 + (sc->rch_cnt - 1), 0);
	sc->rch_cnt--;
	M3_UNLOCK(sc);

	return (0);
}