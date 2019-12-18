#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pfil_head {int dummy; } ;
struct osd {int dummy; } ;
struct ipsec_ctx_data {int af; int enc; int /*<<< orphan*/  sav; TYPE_2__** mp; int /*<<< orphan*/  inp; } ;
struct ifnet {int if_flags; } ;
struct enc_softc {struct ifnet* sc_ifp; } ;
typedef  int int32_t ;
struct TYPE_4__ {int len; struct ifnet* rcvif; } ;
struct TYPE_5__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
 int EACCES ; 
 int EINVAL ; 
 int EPFNOSUPPORT ; 
#define  HHOOK_TYPE_IPSEC_IN 129 
#define  HHOOK_TYPE_IPSEC_OUT 128 
 int /*<<< orphan*/  IFCOUNTER_IBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_UP ; 
 int IPSEC_ENC_AFTER_PFIL ; 
 int IPSEC_ENC_BEFORE ; 
 int /*<<< orphan*/  PFIL_HOOKED_IN (struct pfil_head*) ; 
 int /*<<< orphan*/  PFIL_HOOKED_OUT (struct pfil_head*) ; 
 int PFIL_IN ; 
 int PFIL_OUT ; 
 scalar_t__ PFIL_PASS ; 
 int V_filter_mask_in ; 
 int V_filter_mask_out ; 
 struct pfil_head* V_inet6_pfil_head ; 
 struct pfil_head* V_inet_pfil_head ; 
 int /*<<< orphan*/  enc_bpftap (struct ifnet*,TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pfil_run_hooks (struct pfil_head*,TYPE_2__**,struct ifnet*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enc_hhook(int32_t hhook_type, int32_t hhook_id, void *udata, void *ctx_data,
    void *hdata, struct osd *hosd)
{
	struct ipsec_ctx_data *ctx;
	struct enc_softc *sc;
	struct ifnet *ifp, *rcvif;
	struct pfil_head *ph;
	int pdir;

	sc = (struct enc_softc *)udata;
	ifp = sc->sc_ifp;
	if ((ifp->if_flags & IFF_UP) == 0)
		return (0);

	ctx = (struct ipsec_ctx_data *)ctx_data;
	/* XXX: wrong hook point was used by caller? */
	if (ctx->af != hhook_id)
		return (EPFNOSUPPORT);

	enc_bpftap(ifp, *ctx->mp, ctx->sav, hhook_type, ctx->enc, ctx->af);
	switch (hhook_type) {
	case HHOOK_TYPE_IPSEC_IN:
		if (ctx->enc == IPSEC_ENC_BEFORE) {
			/* Do accounting only once */
			if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
			if_inc_counter(ifp, IFCOUNTER_IBYTES,
			    (*ctx->mp)->m_pkthdr.len);
		}
		if ((ctx->enc & V_filter_mask_in) == 0)
			return (0); /* skip pfil processing */
		pdir = PFIL_IN;
		break;
	case HHOOK_TYPE_IPSEC_OUT:
		if (ctx->enc == IPSEC_ENC_BEFORE) {
			/* Do accounting only once */
			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
			if_inc_counter(ifp, IFCOUNTER_OBYTES,
			    (*ctx->mp)->m_pkthdr.len);
		}
		if ((ctx->enc & V_filter_mask_out) == 0)
			return (0); /* skip pfil processing */
		pdir = PFIL_OUT;
		break;
	default:
		return (EINVAL);
	}

	switch (hhook_id) {
#ifdef INET
	case AF_INET:
		ph = V_inet_pfil_head;
		break;
#endif
#ifdef INET6
	case AF_INET6:
		ph = V_inet6_pfil_head;
		break;
#endif
	default:
		ph = NULL;
	}
	if (ph == NULL || (pdir == PFIL_OUT && !PFIL_HOOKED_OUT(ph)) ||
	    (pdir == PFIL_IN && !PFIL_HOOKED_IN(ph)))
		return (0);
	/* Make a packet looks like it was received on enc(4) */
	rcvif = (*ctx->mp)->m_pkthdr.rcvif;
	(*ctx->mp)->m_pkthdr.rcvif = ifp;
	if (pfil_run_hooks(ph, ctx->mp, ifp, pdir, ctx->inp) != PFIL_PASS) {
		*ctx->mp = NULL; /* consumed by filter */
		return (EACCES);
	}
	(*ctx->mp)->m_pkthdr.rcvif = rcvif;
	enc_bpftap(ifp, *ctx->mp, ctx->sav, hhook_type,
	    IPSEC_ENC_AFTER_PFIL, ctx->af);
	return (0);
}