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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct sc_rchinfo {int ptr; int bufsize; int prevptr; int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; scalar_t__ active; } ;
struct sc_pchinfo {int ptr; int bufsize; int prevptr; int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; scalar_t__ active; } ;
struct sc_info {int pch_cnt; int rch_cnt; struct sc_rchinfo* rch; struct sc_pchinfo* pch; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSP_CONTROL_B ; 
 int /*<<< orphan*/  ASSP_HOST_INT_STATUS ; 
 int ASSP_INT_PENDING ; 
 int DSP2HOST_REQ_TIMER ; 
 int /*<<< orphan*/  HOST_INT_STATUS ; 
 int HV_INT_PENDING ; 
 int /*<<< orphan*/  HW_VOL_COUNTER_MASTER ; 
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 int STOP_ASSP_CLOCK ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int m3_pchan_getptr_internal (struct sc_pchinfo*) ; 
 int m3_rchan_getptr_internal (struct sc_rchinfo*) ; 
 int m3_rd_1 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_wr_1 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_hwvol_mute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_hwvol_step (int /*<<< orphan*/ ,int,int) ; 
 int sndbuf_getblksz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
m3_intr(void *p)
{
	struct sc_info *sc = (struct sc_info *)p;
	struct sc_pchinfo *pch;
	struct sc_rchinfo *rch;
	u_int32_t status, ctl, i, delta;

	M3_DEBUG(INTR, ("m3_intr\n"));

	M3_LOCK(sc);
	status = m3_rd_1(sc, HOST_INT_STATUS);
	if (!status) {
		M3_UNLOCK(sc);
		return;
	}

	m3_wr_1(sc, HOST_INT_STATUS, 0xff); /* ack the int? */

	if (status & HV_INT_PENDING) {
		u_int8_t event;

		event = m3_rd_1(sc, HW_VOL_COUNTER_MASTER);
		switch (event) {
		case 0x99:
			mixer_hwvol_mute(sc->dev);
			break;
		case 0xaa:
			mixer_hwvol_step(sc->dev, 1, 1);
			break;
		case 0x66:
			mixer_hwvol_step(sc->dev, -1, -1);
			break;
		case 0x88:
			break;
		default:
			device_printf(sc->dev, "Unknown HWVOL event\n");
		}
		m3_wr_1(sc, HW_VOL_COUNTER_MASTER, 0x88);

	}

	if (status & ASSP_INT_PENDING) {
		ctl = m3_rd_1(sc, ASSP_CONTROL_B);
		if (!(ctl & STOP_ASSP_CLOCK)) {
			ctl = m3_rd_1(sc, ASSP_HOST_INT_STATUS);
			if (ctl & DSP2HOST_REQ_TIMER) {
				m3_wr_1(sc, ASSP_HOST_INT_STATUS,
					DSP2HOST_REQ_TIMER);
				/*[[ess_update_ptr]]*/
				goto m3_handle_channel_intr;
			}
		}
	}

	goto m3_handle_channel_intr_out;

m3_handle_channel_intr:
	for (i=0 ; i<sc->pch_cnt ; i++) {
		pch = &sc->pch[i];
		if (pch->active) {
			pch->ptr = m3_pchan_getptr_internal(pch);
			delta = pch->bufsize + pch->ptr - pch->prevptr;
			delta %= pch->bufsize;
			if (delta < sndbuf_getblksz(pch->buffer))
				continue;
			pch->prevptr = pch->ptr;
			M3_UNLOCK(sc);
			chn_intr(pch->channel);
			M3_LOCK(sc);
		}
	}
	for (i=0 ; i<sc->rch_cnt ; i++) {
		rch = &sc->rch[i];
		if (rch->active) {
			rch->ptr = m3_rchan_getptr_internal(rch);
			delta = rch->bufsize + rch->ptr - rch->prevptr;
			delta %= rch->bufsize;
			if (delta < sndbuf_getblksz(rch->buffer))
				continue;
			rch->prevptr = rch->ptr;
			M3_UNLOCK(sc);
			chn_intr(rch->channel);
			M3_LOCK(sc);
		}
	}

m3_handle_channel_intr_out:
	M3_UNLOCK(sc);
}