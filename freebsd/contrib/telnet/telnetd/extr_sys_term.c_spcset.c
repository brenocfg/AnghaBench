#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cc_t ;
struct TYPE_7__ {int /*<<< orphan*/  t_lnextc; int /*<<< orphan*/  t_rprntc; int /*<<< orphan*/  t_werasc; int /*<<< orphan*/  t_suspc; int /*<<< orphan*/  t_flushc; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_brkc; int /*<<< orphan*/  t_stopc; int /*<<< orphan*/  t_startc; int /*<<< orphan*/  t_quitc; int /*<<< orphan*/  t_intrc; int /*<<< orphan*/  t_eofc; } ;
struct TYPE_5__ {int /*<<< orphan*/  sg_kill; int /*<<< orphan*/  sg_erase; } ;
struct TYPE_8__ {TYPE_3__ ltc; TYPE_2__ tc; TYPE_1__ sg; } ;

/* Variables and functions */
#define  SLC_ABORT 144 
#define  SLC_AO 143 
#define  SLC_AYT 142 
#define  SLC_BRK 141 
 int SLC_DEFAULT ; 
#define  SLC_EC 140 
#define  SLC_EL 139 
#define  SLC_EOF 138 
#define  SLC_EOR 137 
#define  SLC_EW 136 
 int SLC_FLUSHIN ; 
 int SLC_FLUSHOUT ; 
#define  SLC_FORW1 135 
#define  SLC_IP 134 
#define  SLC_LNEXT 133 
 int SLC_NOSUPPORT ; 
#define  SLC_RP 132 
#define  SLC_SUSP 131 
#define  SLC_SYNCH 130 
 int SLC_VARIABLE ; 
#define  SLC_XOFF 129 
#define  SLC_XON 128 
 TYPE_4__ termbuf ; 

int
spcset(int func, cc_t *valp, cc_t **valpp)
{
	switch(func) {
	case SLC_EOF:
		*valp = termbuf.tc.t_eofc;
		*valpp = (cc_t *)&termbuf.tc.t_eofc;
		return(SLC_VARIABLE);
	case SLC_EC:
		*valp = termbuf.sg.sg_erase;
		*valpp = (cc_t *)&termbuf.sg.sg_erase;
		return(SLC_VARIABLE);
	case SLC_EL:
		*valp = termbuf.sg.sg_kill;
		*valpp = (cc_t *)&termbuf.sg.sg_kill;
		return(SLC_VARIABLE);
	case SLC_IP:
		*valp = termbuf.tc.t_intrc;
		*valpp = (cc_t *)&termbuf.tc.t_intrc;
		return(SLC_VARIABLE|SLC_FLUSHIN|SLC_FLUSHOUT);
	case SLC_ABORT:
		*valp = termbuf.tc.t_quitc;
		*valpp = (cc_t *)&termbuf.tc.t_quitc;
		return(SLC_VARIABLE|SLC_FLUSHIN|SLC_FLUSHOUT);
	case SLC_XON:
		*valp = termbuf.tc.t_startc;
		*valpp = (cc_t *)&termbuf.tc.t_startc;
		return(SLC_VARIABLE);
	case SLC_XOFF:
		*valp = termbuf.tc.t_stopc;
		*valpp = (cc_t *)&termbuf.tc.t_stopc;
		return(SLC_VARIABLE);
	case SLC_AO:
		*valp = termbuf.ltc.t_flushc;
		*valpp = (cc_t *)&termbuf.ltc.t_flushc;
		return(SLC_VARIABLE);
	case SLC_SUSP:
		*valp = termbuf.ltc.t_suspc;
		*valpp = (cc_t *)&termbuf.ltc.t_suspc;
		return(SLC_VARIABLE);
	case SLC_EW:
		*valp = termbuf.ltc.t_werasc;
		*valpp = (cc_t *)&termbuf.ltc.t_werasc;
		return(SLC_VARIABLE);
	case SLC_RP:
		*valp = termbuf.ltc.t_rprntc;
		*valpp = (cc_t *)&termbuf.ltc.t_rprntc;
		return(SLC_VARIABLE);
	case SLC_LNEXT:
		*valp = termbuf.ltc.t_lnextc;
		*valpp = (cc_t *)&termbuf.ltc.t_lnextc;
		return(SLC_VARIABLE);
	case SLC_FORW1:
		*valp = termbuf.tc.t_brkc;
		*valpp = (cc_t *)&termbuf.ltc.t_lnextc;
		return(SLC_VARIABLE);
	case SLC_BRK:
	case SLC_SYNCH:
	case SLC_AYT:
	case SLC_EOR:
		*valp = (cc_t)0;
		*valpp = (cc_t *)0;
		return(SLC_DEFAULT);
	default:
		*valp = (cc_t)0;
		*valpp = (cc_t *)0;
		return(SLC_NOSUPPORT);
	}
}