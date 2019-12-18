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
struct unicx {int dummy; } ;
struct uni_cobisetup {int /*<<< orphan*/  unrec; int /*<<< orphan*/  notify; int /*<<< orphan*/  calling; int /*<<< orphan*/  calledsub; int /*<<< orphan*/  called; int /*<<< orphan*/  facility; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CALLED ; 
 int /*<<< orphan*/  UNI_IE_CALLEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CALLING ; 
 int /*<<< orphan*/  UNI_IE_FACILITY ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int uni_check_ie (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static int
check_cobisetup(struct uni_cobisetup *m, struct unicx *cx)
{
	int ret = 0;

	ret |= uni_check_ie(UNI_IE_FACILITY, (union uni_ieall *)&m->facility, cx);
	ret |= uni_check_ie(UNI_IE_CALLED, (union uni_ieall *)&m->called, cx);
	ret |= uni_check_ie(UNI_IE_CALLEDSUB, (union uni_ieall *)&m->calledsub, cx);
	ret |= uni_check_ie(UNI_IE_CALLING, (union uni_ieall *)&m->calling, cx);
	ret |= uni_check_ie(UNI_IE_NOTIFY, (union uni_ieall *)&m->notify, cx);
	ret |= uni_check_ie(UNI_IE_UNREC, (union uni_ieall *)&m->unrec, cx);

	return ret;
}