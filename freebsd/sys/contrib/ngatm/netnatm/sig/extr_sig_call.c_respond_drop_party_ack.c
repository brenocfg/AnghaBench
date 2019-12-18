#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct uni_ie_epref {int /*<<< orphan*/  flag; int /*<<< orphan*/  epref; } ;
struct TYPE_3__ {int /*<<< orphan*/  cause; int /*<<< orphan*/  epref; } ;
struct TYPE_4__ {TYPE_1__ drop_party_ack; } ;
struct uni_all {TYPE_2__ u; } ;
struct call {int /*<<< orphan*/  uni; int /*<<< orphan*/  mine; int /*<<< orphan*/  cref; } ;

/* Variables and functions */
 int /*<<< orphan*/  MK_IE_CAUSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_IE_EPREF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MK_MSG_ORIG (struct uni_all*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct uni_all* UNI_ALLOC () ; 
 int /*<<< orphan*/  UNI_CAUSE_LOC_USER ; 
 int /*<<< orphan*/  UNI_DROP_PARTY_ACK ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  uni_send_output (struct uni_all*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
respond_drop_party_ack(struct call *c, struct uni_ie_epref *epref,
    u_int cause)
{
	struct uni_all *msg;

	if ((msg = UNI_ALLOC()) == NULL)
		return;

	MK_MSG_ORIG(msg, UNI_DROP_PARTY_ACK, c->cref, !c->mine);
	MK_IE_EPREF(msg->u.drop_party_ack.epref, epref->epref, !epref->flag);
	MK_IE_CAUSE(msg->u.drop_party_ack.cause, UNI_CAUSE_LOC_USER, cause);
	(void)uni_send_output(msg, c->uni);
	UNI_FREE(msg);
}