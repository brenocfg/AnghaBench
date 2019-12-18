#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  int u_int ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct agg_info {scalar_t__ curpwr; int playchns; int active; int /*<<< orphan*/  dev; TYPE_1__ rch; TYPE_2__* pch; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int AGG_RD (struct agg_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AGG_WR (struct agg_info*,int /*<<< orphan*/ ,int,int) ; 
 int HOSTINT_STAT_DSOUND ; 
 int HOSTINT_STAT_HWVOL ; 
#define  HWVOL_DOWN 130 
 int HWVOL_MUTE ; 
#define  HWVOL_NOP 129 
#define  HWVOL_UP 128 
 scalar_t__ PCI_POWERSTATE_D1 ; 
 int /*<<< orphan*/  PORT_HOSTINT_STAT ; 
 int /*<<< orphan*/  PORT_HWVOL_MASTER ; 
 int /*<<< orphan*/  PORT_INT_STAT ; 
 int /*<<< orphan*/  agg_lock (struct agg_info*) ; 
 int /*<<< orphan*/  agg_unlock (struct agg_info*) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_hwvol_mute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_hwvol_step (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  suppress_jitter (TYPE_2__*) ; 
 int /*<<< orphan*/  suppress_rec_jitter (TYPE_1__*) ; 

__attribute__((used)) static void
agg_intr(void *sc)
{
	struct agg_info* ess = sc;
	register u_int8_t status;
	int i;
	u_int m;

	status = AGG_RD(ess, PORT_HOSTINT_STAT, 1);
	if (!status)
		return;

	/* Acknowledge intr. */
	AGG_WR(ess, PORT_HOSTINT_STAT, status, 1);

	if (status & HOSTINT_STAT_DSOUND) {
#ifdef AGG_JITTER_CORRECTION
		agg_lock(ess);
#endif
		if (ess->curpwr <= PCI_POWERSTATE_D1) {
			AGG_WR(ess, PORT_INT_STAT, 1, 2);
#ifdef AGG_JITTER_CORRECTION
			for (i = 0, m = 1; i < ess->playchns; i++, m <<= 1) {
				if (ess->active & m)
					suppress_jitter(ess->pch + i);
			}
			if (ess->active & m)
				suppress_rec_jitter(&ess->rch);
			agg_unlock(ess);
#endif
			for (i = 0, m = 1; i < ess->playchns; i++, m <<= 1) {
				if (ess->active & m) {
					if (ess->curpwr <= PCI_POWERSTATE_D1)
						chn_intr(ess->pch[i].channel);
					else {
						m = 0;
						break;
					}
				}
			}
			if ((ess->active & m)
			    && ess->curpwr <= PCI_POWERSTATE_D1)
				chn_intr(ess->rch.channel);
		}
#ifdef AGG_JITTER_CORRECTION
		else
			agg_unlock(ess);
#endif
	}

	if (status & HOSTINT_STAT_HWVOL) {
		register u_int8_t event;

		agg_lock(ess);
		event = AGG_RD(ess, PORT_HWVOL_MASTER, 1);
		AGG_WR(ess, PORT_HWVOL_MASTER, HWVOL_NOP, 1);
		agg_unlock(ess);

		switch (event) {
		case HWVOL_UP:
			mixer_hwvol_step(ess->dev, 1, 1);
			break;
		case HWVOL_DOWN:
			mixer_hwvol_step(ess->dev, -1, -1);
			break;
		case HWVOL_NOP:
			break;
		default:
			if (event & HWVOL_MUTE) {
				mixer_hwvol_mute(ess->dev);
				break;
			}
			device_printf(ess->dev,
				      "%s: unknown HWVOL event 0x%x\n",
				      device_get_nameunit(ess->dev), event);
		}
	}
}