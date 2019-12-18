#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  present; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/ * ie; } ;
struct TYPE_6__ {TYPE_1__ ie; } ;
struct uni_ie_cause {TYPE_3__ h; TYPE_2__ u; } ;
struct call {TYPE_4__* uni; } ;
struct TYPE_8__ {struct uni_ie_cause cause; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_ISGOOD (struct uni_ie_cause) ; 
 scalar_t__ IE_ISPRESENT (struct uni_ie_cause) ; 
 int /*<<< orphan*/  MK_IE_CAUSE (struct uni_ie_cause,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_CAUSE_IE_INV ; 
 int /*<<< orphan*/  UNI_CAUSE_IE_P ; 
 int /*<<< orphan*/  UNI_CAUSE_LOC_USER ; 
 int /*<<< orphan*/  UNI_CAUSE_MANDAT ; 
 int /*<<< orphan*/  UNI_IE_CAUSE ; 

__attribute__((used)) static void
make_drop_cause(struct call *c, struct uni_ie_cause *cause)
{

	if (!IE_ISGOOD(*cause)) {
		/* 9.5.7.1 paragraph 2 */
		if (IE_ISPRESENT(*cause))
			MK_IE_CAUSE(c->uni->cause, UNI_CAUSE_LOC_USER,
			    UNI_CAUSE_IE_INV);
		else
			MK_IE_CAUSE(c->uni->cause, UNI_CAUSE_LOC_USER,
			    UNI_CAUSE_MANDAT);
		c->uni->cause.u.ie.len = 1;
		c->uni->cause.u.ie.ie[0] = UNI_IE_CAUSE;
		c->uni->cause.h.present |= UNI_CAUSE_IE_P;

	} else if (!IE_ISGOOD(c->uni->cause))
		c->uni->cause = *cause;
}