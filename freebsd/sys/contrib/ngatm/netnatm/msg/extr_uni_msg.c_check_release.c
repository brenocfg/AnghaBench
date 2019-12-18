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
typedef  int u_int ;
struct unicx {int /*<<< orphan*/  pnni; int /*<<< orphan*/  q2932; } ;
struct uni_release {int /*<<< orphan*/  unrec; int /*<<< orphan*/  crankback; int /*<<< orphan*/  facility; int /*<<< orphan*/  uu; int /*<<< orphan*/ * git; int /*<<< orphan*/  notify; int /*<<< orphan*/ * cause; } ;

/* Variables and functions */
 int IE_ISPRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_IE_CAUSE ; 
 int /*<<< orphan*/  UNI_IE_CRANKBACK ; 
 int /*<<< orphan*/  UNI_IE_FACILITY ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 int UNI_NUM_IE_GIT ; 
 int uni_check_ie (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static int
check_release(struct uni_release *m, struct unicx *cx)
{
	int ret = 0;
	u_int i;

	for(i = 0; i < 2 ; i++) {
		ret |= uni_check_ie(UNI_IE_CAUSE, (union uni_ieall *)&m->cause[i], cx);
	}
	ret |= uni_check_ie(UNI_IE_NOTIFY, (union uni_ieall *)&m->notify, cx);
	for(i = 0; i < UNI_NUM_IE_GIT ; i++) {
		ret |= uni_check_ie(UNI_IE_GIT, (union uni_ieall *)&m->git[i], cx);
	}
	if(!(!cx->pnni))
		ret |= IE_ISPRESENT(m->uu);
	else
		ret |= uni_check_ie(UNI_IE_UU, (union uni_ieall *)&m->uu, cx);
	if(!(cx->q2932))
		ret |= IE_ISPRESENT(m->facility);
	else
		ret |= uni_check_ie(UNI_IE_FACILITY, (union uni_ieall *)&m->facility, cx);
	if(!(cx->pnni))
		ret |= IE_ISPRESENT(m->crankback);
	else
		ret |= uni_check_ie(UNI_IE_CRANKBACK, (union uni_ieall *)&m->crankback, cx);
	ret |= uni_check_ie(UNI_IE_UNREC, (union uni_ieall *)&m->unrec, cx);

	return ret;
}