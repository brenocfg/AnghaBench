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
typedef  int /*<<< orphan*/  u_int ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {struct in6_addr addr6; } ;
struct llentry {int lle_refcnt; int /*<<< orphan*/  lle_timer; int /*<<< orphan*/  lle_free; TYPE_1__ r_l3addr; } ;
struct in6_llentry {struct llentry base; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLE_LOCK_INIT (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REQ_INIT (struct llentry*) ; 
 int /*<<< orphan*/  M_LLTABLE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in6_lltable_destroy_lle ; 
 struct in6_llentry* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct llentry *
in6_lltable_new(const struct in6_addr *addr6, u_int flags)
{
	struct in6_llentry *lle;

	lle = malloc(sizeof(struct in6_llentry), M_LLTABLE, M_NOWAIT | M_ZERO);
	if (lle == NULL)		/* NB: caller generates msg */
		return NULL;

	lle->base.r_l3addr.addr6 = *addr6;
	lle->base.lle_refcnt = 1;
	lle->base.lle_free = in6_lltable_destroy_lle;
	LLE_LOCK_INIT(&lle->base);
	LLE_REQ_INIT(&lle->base);
	callout_init(&lle->base.lle_timer, 1);

	return (&lle->base);
}