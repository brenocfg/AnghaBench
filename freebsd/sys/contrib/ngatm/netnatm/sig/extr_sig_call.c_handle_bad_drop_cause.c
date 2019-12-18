#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ act; } ;
struct uni_ie_cause {TYPE_1__ h; } ;
struct call {int /*<<< orphan*/  uni; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (struct uni_ie_cause) ; 
 int /*<<< orphan*/  IE_ISPRESENT (struct uni_ie_cause) ; 
 int /*<<< orphan*/  MK_IE_CAUSE (struct uni_ie_cause,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_CAUSE_LOC_USER ; 
 int /*<<< orphan*/  UNI_CAUSE_UNSPEC ; 
 scalar_t__ UNI_IEACT_DEFAULT ; 
 int /*<<< orphan*/  uni_vfy_remove_cause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_bad_drop_cause(struct call *c, struct uni_ie_cause *cause, int mkcause)
{

	if (IE_ISGOOD(*cause))
		return;

	if (!IE_ISPRESENT(*cause)) {
		/* 9.5.7.1 */
		/* cannot make cause here because we need the 96 error */
		uni_vfy_remove_cause(c->uni);
		return;
	}
	if (cause->h.act != UNI_IEACT_DEFAULT)
		return;

	/* 9.5.7.2 */
	uni_vfy_remove_cause(c->uni);
	if (mkcause)
		MK_IE_CAUSE(*cause, UNI_CAUSE_LOC_USER, UNI_CAUSE_UNSPEC);
}