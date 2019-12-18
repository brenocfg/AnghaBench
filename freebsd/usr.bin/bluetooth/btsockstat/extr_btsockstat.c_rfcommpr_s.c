#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  this ;
struct socket {scalar_t__ so_pcb; } ;
typedef  int /*<<< orphan*/  so ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; int /*<<< orphan*/  dlcs; TYPE_1__ outq; int /*<<< orphan*/  mtu; int /*<<< orphan*/  flags; scalar_t__ l2so; } ;
typedef  TYPE_2__ ng_btsocket_rfcomm_session_t ;
typedef  int /*<<< orphan*/ * ng_btsocket_rfcomm_session_p ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_NEXT (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ kread (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  state2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
rfcommpr_s(kvm_t *kvmd, u_long addr)
{
	static char const * const	states[] = {
	/* NG_BTSOCKET_RFCOMM_SESSION_CLOSED */	       "CLOSED",
	/* NG_BTSOCKET_RFCOMM_SESSION_LISTENING */     "LISTEN",
	/* NG_BTSOCKET_RFCOMM_SESSION_CONNECTING */    "CONNECTING",
	/* NG_BTSOCKET_RFCOMM_SESSION_CONNECTED */     "CONNECTED",
	/* NG_BTSOCKET_RFCOMM_SESSION_OPEN */          "OPEN",
	/* NG_BTSOCKET_RFCOMM_SESSION_DISCONNECTING */ "DISCONNECTING"
	};

	ng_btsocket_rfcomm_session_p	this = NULL, next = NULL;
	ng_btsocket_rfcomm_session_t	s;
	struct socket			so;
	int				first = 1;

	if (addr == 0)
		return;

        if (kread(kvmd, addr, (char *) &this, sizeof(this)) < 0)
		return;

	for ( ; this != NULL; this = next) {
		if (kread(kvmd, (u_long) this, (char *) &s, sizeof(s)) < 0)
			return;
		if (kread(kvmd, (u_long) s.l2so, (char *) &so, sizeof(so)) < 0)
			return;

		next = LIST_NEXT(&s, next);

		if (first) {
			first = 0;
			fprintf(stdout,
"Active RFCOMM sessions\n" \
"%-8.8s %-8.8s %-4.4s %-5.5s %-5.5s %-4.4s %s\n",
				"L2PCB",
				"PCB",
				"Flags",
				"MTU",
				"Out-Q",
				"DLCs",
				"State");
		}

		fprintf(stdout,
"%-8lx %-8lx %-4x %-5d %-5d %-4s %s\n",
			(unsigned long) so.so_pcb,
			(unsigned long) this,
			s.flags,
			s.mtu,
			s.outq.len,
			LIST_EMPTY(&s.dlcs)? "No" : "Yes",
			state2str(s.state));
	}
}