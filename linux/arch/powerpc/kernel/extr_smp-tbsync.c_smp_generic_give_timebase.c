#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int handshake; scalar_t__ ack; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_ITER ; 
 int abs (int) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  kExit ; 
 int /*<<< orphan*/  kSetAndTest ; 
 int /*<<< orphan*/  kTest ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int running ; 
 int start_contest (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* tbsync ; 
 int /*<<< orphan*/  wmb () ; 

void smp_generic_give_timebase(void)
{
	int i, score, score2, old, min=0, max=5000, offset=1000;

	pr_debug("Software timebase sync\n");

	/* if this fails then this kernel won't work anyway... */
	tbsync = kzalloc( sizeof(*tbsync), GFP_KERNEL );
	mb();
	running = 1;

	while (!tbsync->ack)
		barrier();

	pr_debug("Got ack\n");

	/* binary search */
	for (old = -1; old != offset ; offset = (min+max) / 2) {
		score = start_contest(kSetAndTest, offset, NUM_ITER);

		pr_debug("score %d, offset %d\n", score, offset );

		if( score > 0 )
			max = offset;
		else
			min = offset;
		old = offset;
	}
	score = start_contest(kSetAndTest, min, NUM_ITER);
	score2 = start_contest(kSetAndTest, max, NUM_ITER);

	pr_debug("Min %d (score %d), Max %d (score %d)\n",
		 min, score, max, score2);
	score = abs(score);
	score2 = abs(score2);
	offset = (score < score2) ? min : max;

	/* guard against inaccurate mttb */
	for (i = 0; i < 10; i++) {
		start_contest(kSetAndTest, offset, NUM_ITER/10);

		if ((score2 = start_contest(kTest, offset, NUM_ITER)) < 0)
			score2 = -score2;
		if (score2 <= score || score2 < 20)
			break;
	}
	pr_debug("Final offset: %d (%d/%d)\n", offset, score2, NUM_ITER );

	/* exiting */
	tbsync->cmd = kExit;
	wmb();
	tbsync->handshake = 1;
	while (tbsync->ack)
		barrier();
	tbsync->handshake = 0;
	kfree(tbsync);
	tbsync = NULL;
	running = 0;
}