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
struct umtx_q {struct umtx_pi* uq_pi_blocked; } ;
struct umtx_pi {TYPE_1__* pi_owner; } ;
struct TYPE_2__ {struct umtx_q* td_umtxq; } ;

/* Variables and functions */

__attribute__((used)) static struct umtx_pi *
umtx_pi_next(struct umtx_pi *pi)
{
	struct umtx_q *uq_owner;

	if (pi->pi_owner == NULL)
		return (NULL);
	uq_owner = pi->pi_owner->td_umtxq;
	if (uq_owner == NULL)
		return (NULL);
	return (uq_owner->uq_pi_blocked);
}