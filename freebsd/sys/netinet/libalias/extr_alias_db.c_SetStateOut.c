#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* tcp; } ;
struct alias_link {TYPE_2__ data; int /*<<< orphan*/  expire_time; } ;
struct TYPE_4__ {int in; int out; } ;
struct TYPE_6__ {TYPE_1__ state; } ;

/* Variables and functions */
#define  ALIAS_TCP_STATE_CONNECTED 129 
#define  ALIAS_TCP_STATE_DISCONNECTED 128 
 int /*<<< orphan*/  TCP_EXPIRE_CONNECTED ; 
 int /*<<< orphan*/  TCP_EXPIRE_DEAD ; 
 int /*<<< orphan*/  TCP_EXPIRE_SINGLEDEAD ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  panic (char*) ; 

void
SetStateOut(struct alias_link *lnk, int state)
{
	/* TCP output state */
	switch (state) {
		case ALIAS_TCP_STATE_DISCONNECTED:
		if (lnk->data.tcp->state.in != ALIAS_TCP_STATE_CONNECTED)
			lnk->expire_time = TCP_EXPIRE_DEAD;
		else
			lnk->expire_time = TCP_EXPIRE_SINGLEDEAD;
		break;
	case ALIAS_TCP_STATE_CONNECTED:
		if (lnk->data.tcp->state.in == ALIAS_TCP_STATE_CONNECTED)
			lnk->expire_time = TCP_EXPIRE_CONNECTED;
		break;
	default:
#ifdef	_KERNEL
		panic("libalias:SetStateOut() unknown state");
#else
		abort();
#endif
	}
	lnk->data.tcp->state.out = state;
}