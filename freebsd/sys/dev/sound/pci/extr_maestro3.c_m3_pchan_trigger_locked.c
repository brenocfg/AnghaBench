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
typedef  int u_int32_t ;
struct sc_pchinfo {int active; scalar_t__ dac_data; int /*<<< orphan*/  prevptr; int /*<<< orphan*/  ptr; int /*<<< orphan*/  dac_idx; struct sc_info* parent; } ;
struct sc_info {int pch_active_cnt; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALL ; 
 scalar_t__ CDATA_INSTANCE_READY ; 
 int /*<<< orphan*/  CHANGE ; 
 int CLKRUN_GEN_ENABLE ; 
 int /*<<< orphan*/  HOST_INT_CTRL ; 
 scalar_t__ KDATA_MIXER_TASK_NUMBER ; 
 scalar_t__ KDATA_TIMER_COUNT_CURRENT ; 
 scalar_t__ KDATA_TIMER_COUNT_RELOAD ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK_ASSERT (struct sc_info*) ; 
#define  PCMTRIG_ABORT 132 
#define  PCMTRIG_EMLDMARD 131 
#define  PCMTRIG_EMLDMAWR 130 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int m3_chan_active (struct sc_info*) ; 
 int m3_rd_2 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_wr_2 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m3_wr_assp_data (struct sc_info*,scalar_t__,int) ; 

__attribute__((used)) static int
m3_pchan_trigger_locked(kobj_t kobj, void *chdata, int go)
{
	struct sc_pchinfo *ch = chdata;
	struct sc_info *sc = ch->parent;
	u_int32_t data;

	M3_LOCK_ASSERT(sc);
	M3_DEBUG(go == PCMTRIG_START ? CHANGE :
		 go == PCMTRIG_STOP ? CHANGE :
		 go == PCMTRIG_ABORT ? CHANGE :
		 CALL,
		 ("m3_pchan_trigger(dac=%d, go=0x%x{%s})\n", ch->dac_idx, go,
		  go == PCMTRIG_START ? "PCMTRIG_START" :
		  go == PCMTRIG_STOP ? "PCMTRIG_STOP" :
		  go == PCMTRIG_ABORT ? "PCMTRIG_ABORT" : "ignore"));

	switch(go) {
	case PCMTRIG_START:
		if (ch->active) {
			return 0;
		}
		ch->active = 1;
		ch->ptr = 0;
		ch->prevptr = 0;
		sc->pch_active_cnt++;

		/*[[inc_timer_users]]*/
		if (m3_chan_active(sc) == 1) {
	                m3_wr_assp_data(sc, KDATA_TIMER_COUNT_RELOAD, 240);
        	        m3_wr_assp_data(sc, KDATA_TIMER_COUNT_CURRENT, 240);
	                data = m3_rd_2(sc, HOST_INT_CTRL);
        	        m3_wr_2(sc, HOST_INT_CTRL, data | CLKRUN_GEN_ENABLE);
		}

                m3_wr_assp_data(sc, ch->dac_data + CDATA_INSTANCE_READY, 1);
                m3_wr_assp_data(sc, KDATA_MIXER_TASK_NUMBER,
				sc->pch_active_cnt);
		break;

	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		if (ch->active == 0) {
			return 0;
		}
		ch->active = 0;
		sc->pch_active_cnt--;

		/* XXX should the channel be drained? */
		/*[[dec_timer_users]]*/
		if (m3_chan_active(sc) == 0) {
	                m3_wr_assp_data(sc, KDATA_TIMER_COUNT_RELOAD, 0);
        	        m3_wr_assp_data(sc, KDATA_TIMER_COUNT_CURRENT, 0);
                	data = m3_rd_2(sc, HOST_INT_CTRL);
	                m3_wr_2(sc, HOST_INT_CTRL, data & ~CLKRUN_GEN_ENABLE);
		}

                m3_wr_assp_data(sc, ch->dac_data + CDATA_INSTANCE_READY, 0);
                m3_wr_assp_data(sc, KDATA_MIXER_TASK_NUMBER,
				sc->pch_active_cnt);
		break;

	case PCMTRIG_EMLDMAWR:
		/* got play irq, transfer next buffer - ignore if using dma */
	case PCMTRIG_EMLDMARD:
		/* got rec irq, transfer next buffer - ignore if using dma */
	default:
		break;
	}
	return 0;
}