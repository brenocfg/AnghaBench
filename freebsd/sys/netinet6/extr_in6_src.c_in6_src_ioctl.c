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
typedef  int u_long ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_addrpolicy {scalar_t__ label; scalar_t__ use; TYPE_1__ addrmask; TYPE_2__ addr; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ ADDR_LABEL_NOTAPP ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IN6_MASK_ADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  SIOCAADDRCTL_POLICY 129 
#define  SIOCDADDRCTL_POLICY 128 
 int add_addrsel_policyent (struct in6_addrpolicy*) ; 
 int delete_addrsel_policyent (struct in6_addrpolicy*) ; 
 scalar_t__ in6_mask2len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
in6_src_ioctl(u_long cmd, caddr_t data)
{
	struct in6_addrpolicy ent0;

	if (cmd != SIOCAADDRCTL_POLICY && cmd != SIOCDADDRCTL_POLICY)
		return (EOPNOTSUPP); /* check for safety */

	ent0 = *(struct in6_addrpolicy *)data;

	if (ent0.label == ADDR_LABEL_NOTAPP)
		return (EINVAL);
	/* check if the prefix mask is consecutive. */
	if (in6_mask2len(&ent0.addrmask.sin6_addr, NULL) < 0)
		return (EINVAL);
	/* clear trailing garbages (if any) of the prefix address. */
	IN6_MASK_ADDR(&ent0.addr.sin6_addr, &ent0.addrmask.sin6_addr);
	ent0.use = 0;

	switch (cmd) {
	case SIOCAADDRCTL_POLICY:
		return (add_addrsel_policyent(&ent0));
	case SIOCDADDRCTL_POLICY:
		return (delete_addrsel_policyent(&ent0));
	}

	return (0);		/* XXX: compromise compilers */
}