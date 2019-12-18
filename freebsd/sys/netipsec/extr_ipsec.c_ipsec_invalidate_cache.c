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
typedef  scalar_t__ u_int ;
struct secpolicy {int dummy; } ;
struct inpcb {TYPE_1__* inp_sp; } ;
struct TYPE_2__ {int flags; struct secpolicy* sp_out; struct secpolicy* sp_in; } ;

/* Variables and functions */
 int INP_INBOUND_POLICY ; 
 int INP_OUTBOUND_POLICY ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 scalar_t__ IPSEC_DIR_OUTBOUND ; 
 int /*<<< orphan*/  key_freesp (struct secpolicy**) ; 

__attribute__((used)) static void
ipsec_invalidate_cache(struct inpcb *inp, u_int dir)
{
	struct secpolicy *sp;

	INP_WLOCK_ASSERT(inp);
	if (dir == IPSEC_DIR_OUTBOUND) {
		if (inp->inp_sp->flags & INP_INBOUND_POLICY)
			return;
		sp = inp->inp_sp->sp_in;
		inp->inp_sp->sp_in = NULL;
	} else {
		if (inp->inp_sp->flags & INP_OUTBOUND_POLICY)
			return;
		sp = inp->inp_sp->sp_out;
		inp->inp_sp->sp_out = NULL;
	}
	if (sp != NULL)
		key_freesp(&sp); /* release extra reference */
}