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
struct interface {int dummy; } ;
struct ctl_trap {int tr_flags; struct interface* tr_localaddr; int /*<<< orphan*/  tr_addr; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 scalar_t__ ADDR_PORT_EQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t COUNTOF (struct ctl_trap*) ; 
 int TRAP_INUSE ; 
 struct ctl_trap* ctl_traps ; 

__attribute__((used)) static struct ctl_trap *
ctlfindtrap(
	sockaddr_u *raddr,
	struct interface *linter
	)
{
	size_t	n;

	for (n = 0; n < COUNTOF(ctl_traps); n++)
		if ((ctl_traps[n].tr_flags & TRAP_INUSE)
		    && ADDR_PORT_EQ(raddr, &ctl_traps[n].tr_addr)
		    && (linter == ctl_traps[n].tr_localaddr))
			return &ctl_traps[n];

	return NULL;
}