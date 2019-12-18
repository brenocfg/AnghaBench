#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_6__ {scalar_t__ btag; scalar_t__ ftag; } ;
struct TYPE_5__ {int present; } ;
struct uni_ie_traffic {TYPE_3__ t; TYPE_2__ h; } ;
struct TYPE_4__ {int present; } ;
struct uni_ie_bearer {int bclass; int atc; TYPE_1__ h; } ;
typedef  enum uni_traffic_class { ____Placeholder_uni_traffic_class } uni_traffic_class ;

/* Variables and functions */
 int /*<<< orphan*/  BBAD (char*) ; 
 int /*<<< orphan*/  FBAD (char*) ; 
 int /*<<< orphan*/  NOBE (char*) ; 
 int /*<<< orphan*/  NOBT (char*) ; 
 int /*<<< orphan*/  NOFT (char*) ; 
#define  T_CBR23 152 
#define  T_nrtVBR2_6_UBR12 151 
#define  T_rtVBR236 150 
#define  T_rtVBR2_6 149 
#define  UNI_BEARER_A 148 
#define  UNI_BEARER_ATCX_0 147 
#define  UNI_BEARER_ATCX_1 146 
#define  UNI_BEARER_ATCX_2 145 
#define  UNI_BEARER_ATCX_4 144 
#define  UNI_BEARER_ATCX_6 143 
#define  UNI_BEARER_ATCX_8 142 
#define  UNI_BEARER_ATC_ABR 141 
#define  UNI_BEARER_ATC_CBR 140 
#define  UNI_BEARER_ATC_CBR1 139 
#define  UNI_BEARER_ATC_NVBR 138 
#define  UNI_BEARER_ATC_NVBR1 137 
 int UNI_BEARER_ATC_P ; 
#define  UNI_BEARER_ATC_VBR 136 
#define  UNI_BEARER_ATC_VBR1 135 
#define  UNI_BEARER_C 134 
#define  UNI_BEARER_TVP 133 
#define  UNI_BEARER_X 132 
#define  UNI_TRAFFIC_ABR 131 
 int UNI_TRAFFIC_BEST_P ; 
 int UNI_TRAFFIC_BPCR0_P ; 
 int UNI_TRAFFIC_BPCR1_P ; 
#define  UNI_TRAFFIC_CBR1 130 
 int UNI_TRAFFIC_CBR2 ; 
 int UNI_TRAFFIC_CBR3 ; 
 int UNI_TRAFFIC_FPCR0_P ; 
 int UNI_TRAFFIC_FPCR1_P ; 
 int UNI_TRAFFIC_MOPT_P ; 
 int UNI_TRAFFIC_UBR1 ; 
 int UNI_TRAFFIC_UBR2 ; 
#define  UNI_TRAFFIC_nrtVBR1 129 
 int UNI_TRAFFIC_nrtVBR2 ; 
 int UNI_TRAFFIC_nrtVBR3 ; 
 int UNI_TRAFFIC_nrtVBR4 ; 
 int UNI_TRAFFIC_nrtVBR5 ; 
 int UNI_TRAFFIC_nrtVBR6 ; 
#define  UNI_TRAFFIC_rtVBR1 128 
 int UNI_TRAFFIC_rtVBR2 ; 
 int UNI_TRAFFIC_rtVBR3 ; 
 int UNI_TRAFFIC_rtVBR4 ; 
 int UNI_TRAFFIC_rtVBR5 ; 
 int UNI_TRAFFIC_rtVBR6 ; 
 int bcbr3 ; 
 int bmask ; 
 int bvbr16 ; 
 int bvbr23 ; 
 int bvbr4 ; 
 int fcbr3 ; 
 int fmask ; 
 int fvbr16 ; 
 int fvbr23 ; 
 int fvbr4 ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

int
uni_classify_traffic(const struct uni_ie_bearer *bearer,
    const struct uni_ie_traffic *traffic,
    enum uni_traffic_class *fclass, enum uni_traffic_class *bclass,
    char *ebuf, size_t ebufsiz)
{
	u_int tclass;
	u_int ft, bt, be, ftag, btag;

	/* classify */
	switch (bearer->bclass) {

	  case UNI_BEARER_A:
		if (!(bearer->h.present & UNI_BEARER_ATC_P)) {
			tclass = T_CBR23;
			break;
		}
		switch (bearer->atc) {

		  case UNI_BEARER_ATC_CBR1:
			tclass = UNI_TRAFFIC_CBR1;
			break;

		  default:
			snprintf(ebuf, ebufsiz, "bad ATC=%#02x for BCOB-A",
			    bearer->atc);
			return (-1);
		}
		break;

	  case UNI_BEARER_C:
		if (!(bearer->h.present & UNI_BEARER_ATC_P)) {
			tclass = T_nrtVBR2_6_UBR12;
			break;
		}
		switch (bearer->atc) {

		  case UNI_BEARER_ATC_VBR1:
			tclass = UNI_TRAFFIC_rtVBR1;
			break;

		  case UNI_BEARER_ATC_VBR:
			tclass = T_rtVBR236;
			break;

		  case UNI_BEARER_ATC_NVBR1:
			tclass = UNI_TRAFFIC_nrtVBR1;
			break;

		  case UNI_BEARER_ATC_ABR:
			tclass = UNI_TRAFFIC_ABR;
			break;

		  default:
			snprintf(ebuf, ebufsiz, "bad ATC=%#02x for BCOB-C",
			    bearer->atc);
			return (-1);
		}
		break;

	  case UNI_BEARER_X:
		if (!(bearer->h.present & UNI_BEARER_ATC_P)) {
			tclass = T_nrtVBR2_6_UBR12;
			break;
		}
		switch (bearer->atc) {

		  case UNI_BEARER_ATC_CBR1:
			tclass = UNI_TRAFFIC_CBR1;
			break;

		  case UNI_BEARER_ATC_CBR:
		  case UNI_BEARER_ATCX_4:
		  case UNI_BEARER_ATCX_6:
			tclass = T_CBR23;
			break;

		  case UNI_BEARER_ATC_VBR1:
			tclass = UNI_TRAFFIC_rtVBR1;
			break;

		  case UNI_BEARER_ATCX_1:
		  case UNI_BEARER_ATC_VBR:
			tclass = T_rtVBR2_6;
			break;

		  case UNI_BEARER_ATC_NVBR1:
			tclass = UNI_TRAFFIC_nrtVBR1;
			break;

		  case UNI_BEARER_ATCX_0:
		  case UNI_BEARER_ATCX_2:
		  case UNI_BEARER_ATCX_8:
		  case UNI_BEARER_ATC_NVBR:
			tclass = T_nrtVBR2_6_UBR12;
			break;

		  case UNI_BEARER_ATC_ABR:
			tclass = UNI_TRAFFIC_ABR;
			break;

		  default:
			snprintf(ebuf, ebufsiz, "bad ATC=%#02x for BCOB-X",
			    bearer->atc);
			return (-1);
		}
		break;

	  case UNI_BEARER_TVP:
		snprintf(ebuf, ebufsiz, "unsupported bearer class tVP");
		return (-1);

	  default:
		snprintf(ebuf, ebufsiz, "bad bearer class %#02x",
		    bearer->bclass);
		return (-1);
	}

	/*
	 * Now traffic IE
	 */
	ft = traffic->h.present & fmask;
	bt = traffic->h.present & bmask;
	be = traffic->h.present & UNI_TRAFFIC_BEST_P;
	ftag = (traffic->h.present & UNI_TRAFFIC_MOPT_P) && traffic->t.ftag;
	btag = (traffic->h.present & UNI_TRAFFIC_MOPT_P) && traffic->t.btag;

#define NOBE(C)								\
	if (be) {							\
		snprintf(ebuf, ebufsiz, "illegal BE for " C);		\
		return (-1);						\
	}

#define NOFT(C)								\
	if (ftag) {							\
		snprintf(ebuf, ebufsiz, "illegal forward tag in " C);	\
		return (-1);						\
	}

#define NOBT(C)								\
	if (btag) {							\
		snprintf(ebuf, ebufsiz, "illegal backward tag in " C);	\
		return (-1);						\
	}

#define FBAD(C) do {							\
	snprintf(ebuf, ebufsiz, "bad forward CRs for " C);		\
	return (-1);							\
    } while (0)

#define BBAD(C) do {							\
	snprintf(ebuf, ebufsiz, "bad backward CRs for " C);		\
	return (-1);							\
    } while (0)

	switch (tclass) {

	  case UNI_TRAFFIC_CBR1:
		NOBE("CBR.1");
		if (ft != UNI_TRAFFIC_FPCR1_P)
			FBAD("CBR.1");
		NOFT("CBR.1");
		if (bt != UNI_TRAFFIC_BPCR1_P)
			BBAD("CBR.1");
		NOBT("CBR.1");
		*fclass = *bclass = UNI_TRAFFIC_CBR1;
		break;

	  case T_CBR23:
		NOBE("CBR.2/3");
		if (ft == UNI_TRAFFIC_FPCR0_P) {
			*fclass = UNI_TRAFFIC_CBR2;
			NOFT("CBR.2");
		} else if (ft == fcbr3) {
			*fclass = UNI_TRAFFIC_CBR3;
			if (!ftag) {
				snprintf(ebuf, ebufsiz, "need forward tagging for CBR.3");
				return (-1);
			}
		} else
			FBAD("CBR.2/3");
		if (bt == UNI_TRAFFIC_BPCR0_P) {
			*bclass = UNI_TRAFFIC_CBR2;
			NOBT("CBR.2");
		} else if (bt == bcbr3) {
			*bclass = UNI_TRAFFIC_CBR3;
			if (!btag) {
				snprintf(ebuf, ebufsiz, "need backward tagging for CBR.3");
				return (-1);
			}
		} else
			BBAD("CBR.2/3");
		break;

	  case UNI_TRAFFIC_rtVBR1:
		NOBE("rtVBR.1");
		if (ft != fvbr16)
			FBAD("rtVBR.1");
		NOFT("rtVBR.1");
		if (bt != bvbr16)
			BBAD("rtVBR.1");
		NOBT("rtVBR.1");
		*fclass = *bclass = UNI_TRAFFIC_rtVBR1;
		break;

	  case T_rtVBR236:
		NOBE("rtVBR.2/3/6");
		if (ft == fvbr23) {
			if (ftag)
				*fclass = UNI_TRAFFIC_rtVBR3;
			else
				*fclass = UNI_TRAFFIC_rtVBR2;
		} else if (ft == fvbr16) {
			*fclass = UNI_TRAFFIC_rtVBR6;
			NOFT("rtVBR.6");
		} else
			FBAD("rtVBR.2/3/6");
		if (bt == bvbr23) {
			if (btag)
				*bclass = UNI_TRAFFIC_rtVBR3;
			else
				*bclass = UNI_TRAFFIC_rtVBR2;
		} else if (bt == bvbr16) {
			*bclass = UNI_TRAFFIC_rtVBR6;
			NOBT("rtVBR.6");
		} else
			BBAD("rtVBR.2/3/6");
		break;

	  case T_rtVBR2_6:
		NOBE("rtVBR.2-6");
		if (ft == fvbr23) {
			if (ftag)
				*fclass = UNI_TRAFFIC_rtVBR3;
			else
				*fclass = UNI_TRAFFIC_rtVBR2;
		} else if (ft == fvbr4) {
			*fclass = UNI_TRAFFIC_rtVBR4;
		} else if (ft == UNI_TRAFFIC_FPCR1_P) {
			*fclass = UNI_TRAFFIC_rtVBR5;
			NOFT("rtVBR.5");
		} else if (ft == fvbr16) {
			*fclass = UNI_TRAFFIC_rtVBR6;
			NOFT("rtVBR.6");
		} else
			FBAD("rtVBR.2-6");
		if (bt == bvbr23) {
			if (btag)
				*bclass = UNI_TRAFFIC_rtVBR3;
			else
				*bclass = UNI_TRAFFIC_rtVBR2;
		} else if (bt == bvbr4) {
			*bclass = UNI_TRAFFIC_rtVBR4;
		} else if (bt == UNI_TRAFFIC_BPCR1_P) {
			*bclass = UNI_TRAFFIC_rtVBR5;
			NOBT("rtVBR.5");
		} else if (bt == bvbr16) {
			*bclass = UNI_TRAFFIC_rtVBR6;
			NOBT("rtVBR.6");
		} else
			BBAD("rtVBR.2-6");
		break;

	  case UNI_TRAFFIC_nrtVBR1:
		NOBE("nrtVBR.1");
		if (ft != fvbr16)
			FBAD("nrtVBR.1");
		NOFT("nrtVBR.1");
		if (bt != bvbr16)
			BBAD("nrtVBR.1");
		NOBT("nrtVBR.1");
		*fclass = *bclass = UNI_TRAFFIC_nrtVBR1;
		break;

	  case T_nrtVBR2_6_UBR12:
		if (be) {
			if (ft != UNI_TRAFFIC_FPCR1_P)
				FBAD("UBR.1/2");
			if (bt != UNI_TRAFFIC_BPCR1_P)
				BBAD("UBR.1/2");
			if (ftag)
				*fclass = UNI_TRAFFIC_UBR2;
			else
				*fclass = UNI_TRAFFIC_UBR1;
			if (btag)
				*bclass = UNI_TRAFFIC_UBR2;
			else
				*bclass = UNI_TRAFFIC_UBR1;
			break;
		}
		if (ft == fvbr23) {
			if (ftag)
				*fclass = UNI_TRAFFIC_nrtVBR3;
			else
				*fclass = UNI_TRAFFIC_nrtVBR2;
		} else if (ft == fvbr4) {
			*fclass = UNI_TRAFFIC_nrtVBR4;
		} else if (ft == UNI_TRAFFIC_FPCR1_P) {
			*fclass = UNI_TRAFFIC_nrtVBR5;
			NOFT("nrtVBR.5");
		} else if (ft == fvbr16) {
			*fclass = UNI_TRAFFIC_nrtVBR6;
			NOFT("nrtVBR.6");
		} else
			FBAD("nrtVBR.2-6");
		if (bt == bvbr23) {
			if (btag)
				*bclass = UNI_TRAFFIC_nrtVBR3;
			else
				*bclass = UNI_TRAFFIC_nrtVBR2;
		} else if (bt == bvbr4) {
			*bclass = UNI_TRAFFIC_nrtVBR4;
		} else if (bt == UNI_TRAFFIC_BPCR1_P) {
			*bclass = UNI_TRAFFIC_nrtVBR5;
			NOBT("nrtVBR.5");
		} else if (bt == bvbr16) {
			*bclass = UNI_TRAFFIC_nrtVBR6;
			NOBT("nrtVBR.6");
		} else
			BBAD("nrtVBR.2-6");
		break;

	  case UNI_TRAFFIC_ABR:
		NOBE("ABR");
		if (ft != UNI_TRAFFIC_FPCR1_P)
			FBAD("ABR");
		if (bt != UNI_TRAFFIC_BPCR1_P)
			BBAD("ABR");
		NOFT("ABR");
		NOBT("ABR");
		*fclass = *bclass = UNI_TRAFFIC_ABR;
		break;
	}

	return (0);
}