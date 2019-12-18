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
struct umtx_pi {TYPE_2__* pi_owner; } ;
struct TYPE_4__ {TYPE_1__* td_umtxq; } ;
struct TYPE_3__ {int /*<<< orphan*/  uq_pi_contested; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct umtx_pi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_link ; 
 int /*<<< orphan*/  umtx_lock ; 

__attribute__((used)) static void
umtx_pi_disown(struct umtx_pi *pi)
{

	mtx_assert(&umtx_lock, MA_OWNED);
	TAILQ_REMOVE(&pi->pi_owner->td_umtxq->uq_pi_contested, pi, pi_link);
	pi->pi_owner = NULL;
}