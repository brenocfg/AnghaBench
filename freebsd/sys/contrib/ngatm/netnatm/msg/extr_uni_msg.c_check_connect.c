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
struct unicx {int /*<<< orphan*/  pnni; int /*<<< orphan*/  q2932; } ;
struct uni_connect {int /*<<< orphan*/  unrec; int /*<<< orphan*/  report; int /*<<< orphan*/  called_soft; int /*<<< orphan*/  abradd; int /*<<< orphan*/  abrsetup; int /*<<< orphan*/  facility; int /*<<< orphan*/  exqos; int /*<<< orphan*/  traffic; int /*<<< orphan*/  uu; int /*<<< orphan*/ * git; int /*<<< orphan*/  eetd; int /*<<< orphan*/  connedsub; int /*<<< orphan*/  conned; int /*<<< orphan*/  notify; int /*<<< orphan*/  epref; int /*<<< orphan*/  connid; int /*<<< orphan*/  blli; int /*<<< orphan*/  aal; } ;

/* Variables and functions */
 int IE_ISPRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_IE_AAL ; 
 int /*<<< orphan*/  UNI_IE_ABRADD ; 
 int /*<<< orphan*/  UNI_IE_ABRSETUP ; 
 int /*<<< orphan*/  UNI_IE_BLLI ; 
 int /*<<< orphan*/  UNI_IE_CALLED_SOFT ; 
 int /*<<< orphan*/  UNI_IE_CONNED ; 
 int /*<<< orphan*/  UNI_IE_CONNEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CONNID ; 
 int /*<<< orphan*/  UNI_IE_EETD ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_EXQOS ; 
 int /*<<< orphan*/  UNI_IE_FACILITY ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int /*<<< orphan*/  UNI_IE_REPORT ; 
 int /*<<< orphan*/  UNI_IE_TRAFFIC ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 size_t UNI_NUM_IE_GIT ; 
 int uni_check_ie (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static int
check_connect(struct uni_connect *m, struct unicx *cx)
{
	int ret = 0;
	u_int i;

	ret |= uni_check_ie(UNI_IE_AAL, (union uni_ieall *)&m->aal, cx);
	ret |= uni_check_ie(UNI_IE_BLLI, (union uni_ieall *)&m->blli, cx);
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->connid);
	else
		ret |= uni_check_ie(UNI_IE_CONNID, (union uni_ieall *)&m->connid, cx);
	ret |= uni_check_ie(UNI_IE_EPREF, (union uni_ieall *)&m->epref, cx);
	ret |= uni_check_ie(UNI_IE_NOTIFY, (union uni_ieall *)&m->notify, cx);
	ret |= uni_check_ie(UNI_IE_CONNED, (union uni_ieall *)&m->conned, cx);
	ret |= uni_check_ie(UNI_IE_CONNEDSUB, (union uni_ieall *)&m->connedsub, cx);
	ret |= uni_check_ie(UNI_IE_EETD, (union uni_ieall *)&m->eetd, cx);
	for(i = 0; i < UNI_NUM_IE_GIT ; i++) {
		ret |= uni_check_ie(UNI_IE_GIT, (union uni_ieall *)&m->git[i], cx);
	}
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->uu);
	else
		ret |= uni_check_ie(UNI_IE_UU, (union uni_ieall *)&m->uu, cx);
	ret |= uni_check_ie(UNI_IE_TRAFFIC, (union uni_ieall *)&m->traffic, cx);
	ret |= uni_check_ie(UNI_IE_EXQOS, (union uni_ieall *)&m->exqos, cx);
	if(!(cx->q2932))
		ret |= IE_ISPRESENT(m->facility);
	else
		ret |= uni_check_ie(UNI_IE_FACILITY, (union uni_ieall *)&m->facility, cx);
	ret |= uni_check_ie(UNI_IE_ABRSETUP, (union uni_ieall *)&m->abrsetup, cx);
	ret |= uni_check_ie(UNI_IE_ABRADD, (union uni_ieall *)&m->abradd, cx);
	if(!(cx->pnni))
		ret |= IE_ISPRESENT(m->called_soft);
	else
		ret |= uni_check_ie(UNI_IE_CALLED_SOFT, (union uni_ieall *)&m->called_soft, cx);
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->report);
	else
		ret |= uni_check_ie(UNI_IE_REPORT, (union uni_ieall *)&m->report, cx);
	ret |= uni_check_ie(UNI_IE_UNREC, (union uni_ieall *)&m->unrec, cx);

	return ret;
}