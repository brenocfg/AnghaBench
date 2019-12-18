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
struct uni_status {int /*<<< orphan*/  unrec; int /*<<< orphan*/  epstate; int /*<<< orphan*/  epref; int /*<<< orphan*/  cause; int /*<<< orphan*/  callstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CALLSTATE ; 
 int /*<<< orphan*/  UNI_IE_CAUSE ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_EPSTATE ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int uni_check_ie (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static int
check_status(struct uni_status *m, struct unicx *cx)
{
	int ret = 0;

	ret |= uni_check_ie(UNI_IE_CALLSTATE, (union uni_ieall *)&m->callstate, cx);
	ret |= uni_check_ie(UNI_IE_CAUSE, (union uni_ieall *)&m->cause, cx);
	ret |= uni_check_ie(UNI_IE_EPREF, (union uni_ieall *)&m->epref, cx);
	ret |= uni_check_ie(UNI_IE_EPSTATE, (union uni_ieall *)&m->epstate, cx);
	ret |= uni_check_ie(UNI_IE_UNREC, (union uni_ieall *)&m->unrec, cx);

	return ret;
}