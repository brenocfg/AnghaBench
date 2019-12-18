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
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct sppp {int* state; TYPE_1__ lcp; int /*<<< orphan*/ * ch; } ;
struct cp {size_t protoidx; int /*<<< orphan*/  TO; } ;

/* Variables and functions */
#define  STATE_ACK_RCVD 137 
#define  STATE_ACK_SENT 136 
#define  STATE_CLOSED 135 
#define  STATE_CLOSING 134 
#define  STATE_INITIAL 133 
#define  STATE_OPENED 132 
#define  STATE_REQ_SENT 131 
#define  STATE_STARTING 130 
#define  STATE_STOPPED 129 
#define  STATE_STOPPING 128 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sppp_cp_change_state(const struct cp *cp, struct sppp *sp, int newstate)
{
	sp->state[cp->protoidx] = newstate;

	callout_stop (&sp->ch[cp->protoidx]);

	switch (newstate) {
	case STATE_INITIAL:
	case STATE_STARTING:
	case STATE_CLOSED:
	case STATE_STOPPED:
	case STATE_OPENED:
		break;
	case STATE_CLOSING:
	case STATE_STOPPING:
	case STATE_REQ_SENT:
	case STATE_ACK_RCVD:
	case STATE_ACK_SENT:
		callout_reset(&sp->ch[cp->protoidx], sp->lcp.timeout,
			      cp->TO, (void *)sp);
		break;
	}
}