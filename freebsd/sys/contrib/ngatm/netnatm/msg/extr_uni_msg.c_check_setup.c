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
typedef  union uni_ieall {int dummy; } uni_ieall ;
typedef  size_t u_int ;
struct unicx {int /*<<< orphan*/  pnni; } ;
struct uni_setup {int /*<<< orphan*/  unrec; int /*<<< orphan*/  mdcr; int /*<<< orphan*/  report; int /*<<< orphan*/ * dtl; int /*<<< orphan*/  dtl_repeat; int /*<<< orphan*/  called_soft; int /*<<< orphan*/  calling_soft; int /*<<< orphan*/  cscope; int /*<<< orphan*/  abradd; int /*<<< orphan*/  abrsetup; int /*<<< orphan*/  exqos; int /*<<< orphan*/  lij_seqno; int /*<<< orphan*/  lij_param; int /*<<< orphan*/  lij_callid; int /*<<< orphan*/ * git; int /*<<< orphan*/  uu; int /*<<< orphan*/  mintraffic; int /*<<< orphan*/  atraffic; int /*<<< orphan*/  epref; int /*<<< orphan*/ * tns; int /*<<< orphan*/  scompl; int /*<<< orphan*/  notify; int /*<<< orphan*/  eetd; int /*<<< orphan*/  qos; int /*<<< orphan*/  connid; int /*<<< orphan*/ * callingsub; int /*<<< orphan*/  calling; int /*<<< orphan*/ * calledsub; int /*<<< orphan*/  called; int /*<<< orphan*/ * blli; int /*<<< orphan*/  blli_repeat; int /*<<< orphan*/  bhli; int /*<<< orphan*/  bearer; int /*<<< orphan*/  traffic; int /*<<< orphan*/  aal; } ;

/* Variables and functions */
 int IE_ISPRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_IE_AAL ; 
 int /*<<< orphan*/  UNI_IE_ABRADD ; 
 int /*<<< orphan*/  UNI_IE_ABRSETUP ; 
 int /*<<< orphan*/  UNI_IE_ATRAFFIC ; 
 int /*<<< orphan*/  UNI_IE_BEARER ; 
 int /*<<< orphan*/  UNI_IE_BHLI ; 
 int /*<<< orphan*/  UNI_IE_BLLI ; 
 int /*<<< orphan*/  UNI_IE_CALLED ; 
 int /*<<< orphan*/  UNI_IE_CALLEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CALLED_SOFT ; 
 int /*<<< orphan*/  UNI_IE_CALLING ; 
 int /*<<< orphan*/  UNI_IE_CALLINGSUB ; 
 int /*<<< orphan*/  UNI_IE_CALLING_SOFT ; 
 int /*<<< orphan*/  UNI_IE_CONNID ; 
 int /*<<< orphan*/  UNI_IE_CSCOPE ; 
 int /*<<< orphan*/  UNI_IE_DTL ; 
 int /*<<< orphan*/  UNI_IE_EETD ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_EXQOS ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int /*<<< orphan*/  UNI_IE_LIJ_CALLID ; 
 int /*<<< orphan*/  UNI_IE_LIJ_PARAM ; 
 int /*<<< orphan*/  UNI_IE_LIJ_SEQNO ; 
 int /*<<< orphan*/  UNI_IE_MDCR ; 
 int /*<<< orphan*/  UNI_IE_MINTRAFFIC ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int /*<<< orphan*/  UNI_IE_QOS ; 
 int /*<<< orphan*/  UNI_IE_REPEAT ; 
 int /*<<< orphan*/  UNI_IE_REPORT ; 
 int /*<<< orphan*/  UNI_IE_SCOMPL ; 
 int /*<<< orphan*/  UNI_IE_TNS ; 
 int /*<<< orphan*/  UNI_IE_TRAFFIC ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 size_t UNI_NUM_IE_BLLI ; 
 size_t UNI_NUM_IE_CALLEDSUB ; 
 size_t UNI_NUM_IE_CALLINGSUB ; 
 size_t UNI_NUM_IE_DTL ; 
 size_t UNI_NUM_IE_GIT ; 
 size_t UNI_NUM_IE_TNS ; 
 int uni_check_ie (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static int
check_setup(struct uni_setup *m, struct unicx *cx)
{
	int ret = 0;
	u_int i;

	ret |= uni_check_ie(UNI_IE_AAL, (union uni_ieall *)&m->aal, cx);
	ret |= uni_check_ie(UNI_IE_TRAFFIC, (union uni_ieall *)&m->traffic, cx);
	ret |= uni_check_ie(UNI_IE_BEARER, (union uni_ieall *)&m->bearer, cx);
	ret |= uni_check_ie(UNI_IE_BHLI, (union uni_ieall *)&m->bhli, cx);
	ret |= uni_check_ie(UNI_IE_REPEAT, (union uni_ieall *)&m->blli_repeat, cx);
	for(i = 0; i < UNI_NUM_IE_BLLI ; i++) {
		ret |= uni_check_ie(UNI_IE_BLLI, (union uni_ieall *)&m->blli[i], cx);
	}
	ret |= uni_check_ie(UNI_IE_CALLED, (union uni_ieall *)&m->called, cx);
	for(i = 0; i < UNI_NUM_IE_CALLEDSUB ; i++) {
		ret |= uni_check_ie(UNI_IE_CALLEDSUB, (union uni_ieall *)&m->calledsub[i], cx);
	}
	ret |= uni_check_ie(UNI_IE_CALLING, (union uni_ieall *)&m->calling, cx);
	for(i = 0; i < UNI_NUM_IE_CALLINGSUB ; i++) {
		ret |= uni_check_ie(UNI_IE_CALLINGSUB, (union uni_ieall *)&m->callingsub[i], cx);
	}
	ret |= uni_check_ie(UNI_IE_CONNID, (union uni_ieall *)&m->connid, cx);
	ret |= uni_check_ie(UNI_IE_QOS, (union uni_ieall *)&m->qos, cx);
	ret |= uni_check_ie(UNI_IE_EETD, (union uni_ieall *)&m->eetd, cx);
	ret |= uni_check_ie(UNI_IE_NOTIFY, (union uni_ieall *)&m->notify, cx);
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->scompl);
	else
		ret |= uni_check_ie(UNI_IE_SCOMPL, (union uni_ieall *)&m->scompl, cx);
	for(i = 0; i < UNI_NUM_IE_TNS ; i++) {
		ret |= uni_check_ie(UNI_IE_TNS, (union uni_ieall *)&m->tns[i], cx);
	}
	ret |= uni_check_ie(UNI_IE_EPREF, (union uni_ieall *)&m->epref, cx);
	ret |= uni_check_ie(UNI_IE_ATRAFFIC, (union uni_ieall *)&m->atraffic, cx);
	ret |= uni_check_ie(UNI_IE_MINTRAFFIC, (union uni_ieall *)&m->mintraffic, cx);
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->uu);
	else
		ret |= uni_check_ie(UNI_IE_UU, (union uni_ieall *)&m->uu, cx);
	for(i = 0; i < UNI_NUM_IE_GIT ; i++) {
		ret |= uni_check_ie(UNI_IE_GIT, (union uni_ieall *)&m->git[i], cx);
	}
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->lij_callid);
	else
		ret |= uni_check_ie(UNI_IE_LIJ_CALLID, (union uni_ieall *)&m->lij_callid, cx);
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->lij_param);
	else
		ret |= uni_check_ie(UNI_IE_LIJ_PARAM, (union uni_ieall *)&m->lij_param, cx);
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->lij_seqno);
	else
		ret |= uni_check_ie(UNI_IE_LIJ_SEQNO, (union uni_ieall *)&m->lij_seqno, cx);
	ret |= uni_check_ie(UNI_IE_EXQOS, (union uni_ieall *)&m->exqos, cx);
	ret |= uni_check_ie(UNI_IE_ABRSETUP, (union uni_ieall *)&m->abrsetup, cx);
	ret |= uni_check_ie(UNI_IE_ABRADD, (union uni_ieall *)&m->abradd, cx);
	ret |= uni_check_ie(UNI_IE_CSCOPE, (union uni_ieall *)&m->cscope, cx);
	if(!(cx->pnni))
		ret |= IE_ISPRESENT(m->calling_soft);
	else
		ret |= uni_check_ie(UNI_IE_CALLING_SOFT, (union uni_ieall *)&m->calling_soft, cx);
	if(!(cx->pnni))
		ret |= IE_ISPRESENT(m->called_soft);
	else
		ret |= uni_check_ie(UNI_IE_CALLED_SOFT, (union uni_ieall *)&m->called_soft, cx);
	if(!(cx->pnni))
		ret |= IE_ISPRESENT(m->dtl_repeat);
	else
		ret |= uni_check_ie(UNI_IE_REPEAT, (union uni_ieall *)&m->dtl_repeat, cx);
	for(i = 0; i < UNI_NUM_IE_DTL ; i++) {
		if(!(cx->pnni))
			ret |= IE_ISPRESENT(m->dtl[i]);
		else
			ret |= uni_check_ie(UNI_IE_DTL, (union uni_ieall *)&m->dtl[i], cx);
	}
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->report);
	else
		ret |= uni_check_ie(UNI_IE_REPORT, (union uni_ieall *)&m->report, cx);
	ret |= uni_check_ie(UNI_IE_MDCR, (union uni_ieall *)&m->mdcr, cx);
	ret |= uni_check_ie(UNI_IE_UNREC, (union uni_ieall *)&m->unrec, cx);

	return ret;
}