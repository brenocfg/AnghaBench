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
struct unicx {int dummy; } ;
struct uni_leaf_setup_fail {int /*<<< orphan*/  unrec; int /*<<< orphan*/ * tns; int /*<<< orphan*/  lij_seqno; int /*<<< orphan*/  calledsub; int /*<<< orphan*/  called; int /*<<< orphan*/  cause; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CALLED ; 
 int /*<<< orphan*/  UNI_IE_CALLEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CAUSE ; 
 int /*<<< orphan*/  UNI_IE_LIJ_SEQNO ; 
 int /*<<< orphan*/  UNI_IE_TNS ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 size_t UNI_NUM_IE_TNS ; 
 int uni_check_ie (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static int
check_leaf_setup_fail(struct uni_leaf_setup_fail *m, struct unicx *cx)
{
	int ret = 0;
	u_int i;

	ret |= uni_check_ie(UNI_IE_CAUSE, (union uni_ieall *)&m->cause, cx);
	ret |= uni_check_ie(UNI_IE_CALLED, (union uni_ieall *)&m->called, cx);
	ret |= uni_check_ie(UNI_IE_CALLEDSUB, (union uni_ieall *)&m->calledsub, cx);
	ret |= uni_check_ie(UNI_IE_LIJ_SEQNO, (union uni_ieall *)&m->lij_seqno, cx);
	for(i = 0; i < UNI_NUM_IE_TNS ; i++) {
		ret |= uni_check_ie(UNI_IE_TNS, (union uni_ieall *)&m->tns[i], cx);
	}
	ret |= uni_check_ie(UNI_IE_UNREC, (union uni_ieall *)&m->unrec, cx);

	return ret;
}