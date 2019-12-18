#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout_t ;
struct mn_softc {unsigned int falc_irq; char* name; unsigned int falc_state; unsigned int framer_state; TYPE_2__* f54r; int /*<<< orphan*/  cnt_rbc; int /*<<< orphan*/  cnt_cec3; int /*<<< orphan*/  cnt_cec2; int /*<<< orphan*/  cnt_ebc; int /*<<< orphan*/  cnt_cec1; int /*<<< orphan*/  cnt_cvc; int /*<<< orphan*/  cnt_fec; TYPE_1__** ch; } ;
struct TYPE_10__ {int if_flags; } ;
struct TYPE_9__ {scalar_t__ pp_up; scalar_t__ pp_down; } ;
struct TYPE_8__ {unsigned int gis; int isr0; int isr1; int isr2; unsigned int isr3; int frs0; int frs1; int rsw; unsigned int rsp; scalar_t__ rbc; scalar_t__ cec3; scalar_t__ cec2; scalar_t__ ebc; scalar_t__ cec1; scalar_t__ cvc; scalar_t__ fec; } ;
struct TYPE_7__ {TYPE_3__ ifsppp; } ;

/* Variables and functions */
 int IFF_UP ; 
 size_t M32_CHAN ; 
 TYPE_5__* SP2IFP (TYPE_3__*) ; 
 int hz ; 
 size_t i ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned int,...) ; 
 TYPE_3__* sp ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

__attribute__((used)) static void
f54_intr(struct mn_softc *sc)
{
	unsigned g, u, s;

	g = sc->f54r->gis;
	u = sc->f54r->isr0 << 24;
	u |= sc->f54r->isr1 << 16;
	u |= sc->f54r->isr2 <<  8;
	u |= sc->f54r->isr3;
	sc->falc_irq = u;
	/* don't chat about the 1 sec heart beat */
	if (u & ~0x40) {
#if 0
		printf("%s*: FALC54 IRQ GIS:%02x %b\n", sc->name, g, u, "\20"
		    "\40RME\37RFS\36T8MS\35RMB\34CASC\33CRC4\32SA6SC\31RPF"
		    "\30b27\27RDO\26ALLS\25XDU\24XMB\23b22\22XLSC\21XPR"
		    "\20FAR\17LFA\16MFAR\15T400MS\14AIS\13LOS\12RAR\11RA"
		    "\10ES\7SEC\6LMFA16\5AIS16\4RA16\3API\2SLN\1SLP");
#endif
		s = sc->f54r->frs0 << 24;
		s |= sc->f54r->frs1 << 16;
		s |= sc->f54r->rsw <<  8;
		s |= sc->f54r->rsp;
		sc->falc_state = s;

		s &= ~0x01844038;	/* undefined or static bits */
		s &= ~0x00009fc7;	/* bits we don't care about */
		s &= ~0x00780000;	/* XXX: TS16 related */
		s &= ~0x06000000;	/* XXX: Multiframe related */
#if 0
		printf("%s*: FALC54 Status %b\n", sc->name, s, "\20"
		    "\40LOS\37AIS\36LFA\35RRA\34AUXP\33NMF\32LMFA\31frs0.0"
		    "\30frs1.7\27TS16RA\26TS16LOS\25TS16AIS\24TS16LFA\23frs1.2\22XLS\21XLO"
		    "\20RS1\17rsw.6\16RRA\15RY0\14RY1\13RY2\12RY3\11RY4"
		    "\10SI1\7SI2\6rsp.5\5rsp.4\4rsp.3\3RSIF\2RS13\1RS15");
#endif
		if (s != sc->framer_state) {
#if 0
			for (i = 0; i < M32_CHAN; i++) {
				if (!sc->ch[i])
					continue;
			        sp = &sc->ch[i]->ifsppp;
				if (!(SP2IFP(sp)->if_flags & IFF_UP))
					continue;
				if (s) 
					timeout((timeout_t *)sp->pp_down, sp, 1 * hz);
				else 
					timeout((timeout_t *)sp->pp_up, sp, 1 * hz);
			}
#endif
			sc->framer_state = s;
		}
	} 
	/* Once per second check error counters */
	/* XXX: not clear if this is actually ok */
	if (!(u & 0x40))
		return;
	sc->cnt_fec  += sc->f54r->fec;
	sc->cnt_cvc  += sc->f54r->cvc;
	sc->cnt_cec1 += sc->f54r->cec1;
	sc->cnt_ebc  += sc->f54r->ebc;
	sc->cnt_cec2 += sc->f54r->cec2;
	sc->cnt_cec3 += sc->f54r->cec3;
	sc->cnt_rbc  += sc->f54r->rbc;
}