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
struct call {int cstate; int /*<<< orphan*/  mine; int /*<<< orphan*/  cref; TYPE_2__* uni; } ;
typedef  enum call_state { ____Placeholder_call_state } call_state ;
struct TYPE_4__ {scalar_t__ proto; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int,char*) ; 
 int CALLST_N1 ; 
 int CALLST_N12 ; 
 int CALLST_NULL ; 
 int CALLST_U1 ; 
 int CALLST_U12 ; 
 scalar_t__ UNIPROTO_UNI40N ; 
 scalar_t__ UNIPROTO_UNI40U ; 
 int /*<<< orphan*/  UNI_FAC_CALL ; 
 int /*<<< orphan*/  VERBOSE (TYPE_2__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* callstates ; 

__attribute__((used)) static __inline void
set_call_state(struct call *c, enum call_state state)
{
	ASSERT(state == CALLST_NULL ||
	    (c->uni->proto == UNIPROTO_UNI40U &&
	     (state >= CALLST_U1 && state <= CALLST_U12)) ||
	    (c->uni->proto == UNIPROTO_UNI40N &&
	     (state >= CALLST_N1 && state <= CALLST_N12)),
	    ("setting wrong callstate for proto %u: %u", c->uni->proto, state));

	if (c->cstate != state) {
		VERBOSE(c->uni, UNI_FAC_CALL, 1, "call %d/%d %s -> %s",
		    c->cref, c->mine, callstates[c->cstate].name,
		    callstates[state].name);
		c->cstate = state;
	}
}