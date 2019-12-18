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
struct ctl_trap {int tr_flags; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 int TRAP_CONFIGURED ; 
 int TRAP_TYPE_CONFIG ; 
 struct ctl_trap* ctlfindtrap (int /*<<< orphan*/ *,struct interface*) ; 
 int /*<<< orphan*/  num_ctl_traps ; 

int
ctlclrtrap(
	sockaddr_u *raddr,
	struct interface *linter,
	int traptype
	)
{
	register struct ctl_trap *tp;

	if ((tp = ctlfindtrap(raddr, linter)) == NULL)
		return (0);

	if (tp->tr_flags & TRAP_CONFIGURED
	    && traptype != TRAP_TYPE_CONFIG)
		return (0);

	tp->tr_flags = 0;
	num_ctl_traps--;
	return (1);
}