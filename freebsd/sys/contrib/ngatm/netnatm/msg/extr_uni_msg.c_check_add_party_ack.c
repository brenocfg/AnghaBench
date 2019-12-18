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
struct uni_add_party_ack {int /*<<< orphan*/  unrec; int /*<<< orphan*/  called_soft; int /*<<< orphan*/ * git; int /*<<< orphan*/  uu; int /*<<< orphan*/  connedsub; int /*<<< orphan*/  conned; int /*<<< orphan*/  eetd; int /*<<< orphan*/  notify; int /*<<< orphan*/  blli; int /*<<< orphan*/  aal; int /*<<< orphan*/  epref; } ;

/* Variables and functions */
 int IE_ISPRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_IE_AAL ; 
 int /*<<< orphan*/  UNI_IE_BLLI ; 
 int /*<<< orphan*/  UNI_IE_CALLED_SOFT ; 
 int /*<<< orphan*/  UNI_IE_CONNED ; 
 int /*<<< orphan*/  UNI_IE_CONNEDSUB ; 
 int /*<<< orphan*/  UNI_IE_EETD ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 size_t UNI_NUM_IE_GIT ; 
 int uni_check_ie (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static int
check_add_party_ack(struct uni_add_party_ack *m, struct unicx *cx)
{
	int ret = 0;
	u_int i;

	ret |= uni_check_ie(UNI_IE_EPREF, (union uni_ieall *)&m->epref, cx);
	ret |= uni_check_ie(UNI_IE_AAL, (union uni_ieall *)&m->aal, cx);
	ret |= uni_check_ie(UNI_IE_BLLI, (union uni_ieall *)&m->blli, cx);
	ret |= uni_check_ie(UNI_IE_NOTIFY, (union uni_ieall *)&m->notify, cx);
	ret |= uni_check_ie(UNI_IE_EETD, (union uni_ieall *)&m->eetd, cx);
	ret |= uni_check_ie(UNI_IE_CONNED, (union uni_ieall *)&m->conned, cx);
	ret |= uni_check_ie(UNI_IE_CONNEDSUB, (union uni_ieall *)&m->connedsub, cx);
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->uu);
	else
		ret |= uni_check_ie(UNI_IE_UU, (union uni_ieall *)&m->uu, cx);
	for(i = 0; i < UNI_NUM_IE_GIT ; i++) {
		ret |= uni_check_ie(UNI_IE_GIT, (union uni_ieall *)&m->git[i], cx);
	}
	if(!(cx->pnni))
		ret |= IE_ISPRESENT(m->called_soft);
	else
		ret |= uni_check_ie(UNI_IE_CALLED_SOFT, (union uni_ieall *)&m->called_soft, cx);
	ret |= uni_check_ie(UNI_IE_UNREC, (union uni_ieall *)&m->unrec, cx);

	return ret;
}