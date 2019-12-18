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

/* Variables and functions */
 int /*<<< orphan*/  ARC4_ENTR_HAVE ; 
 int /*<<< orphan*/  ARC4_ENTR_NONE ; 
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  arc4rand_iniseed_state ; 
 int /*<<< orphan*/  atomic_cmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  random_alg_context ; 
 int /*<<< orphan*/  rsel ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
randomdev_unblock(void)
{

	selwakeuppri(&rsel, PUSER);
	wakeup(&random_alg_context);
	printf("random: unblocking device.\n");
	/* Do random(9) a favour while we are about it. */
	(void)atomic_cmpset_int(&arc4rand_iniseed_state, ARC4_ENTR_NONE, ARC4_ENTR_HAVE);
}