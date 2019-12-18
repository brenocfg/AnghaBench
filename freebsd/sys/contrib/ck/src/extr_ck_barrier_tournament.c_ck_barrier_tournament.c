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
struct ck_barrier_tournament_state {size_t vpid; int /*<<< orphan*/  sense; } ;
struct ck_barrier_tournament_round {int role; int /*<<< orphan*/  opponent; int /*<<< orphan*/  flag; } ;
struct ck_barrier_tournament {int size; int /*<<< orphan*/  rounds; } ;

/* Variables and functions */
#define  CK_BARRIER_TOURNAMENT_BYE 132 
#define  CK_BARRIER_TOURNAMENT_CHAMPION 131 
#define  CK_BARRIER_TOURNAMENT_DROPOUT 130 
#define  CK_BARRIER_TOURNAMENT_LOSER 129 
#define  CK_BARRIER_TOURNAMENT_WINNER 128 
 int /*<<< orphan*/  ck_pr_fence_memory () ; 
 struct ck_barrier_tournament_round** ck_pr_load_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_pr_load_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_pr_stall () ; 
 int /*<<< orphan*/  ck_pr_store_uint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ck_barrier_tournament(struct ck_barrier_tournament *barrier,
    struct ck_barrier_tournament_state *state)
{
	struct ck_barrier_tournament_round **rounds = ck_pr_load_ptr(&barrier->rounds);
	int round = 1;

	if (barrier->size == 1)
		return;

	for (;; ++round) {
		switch (rounds[state->vpid][round].role) {
		case CK_BARRIER_TOURNAMENT_BYE:
			break;
		case CK_BARRIER_TOURNAMENT_CHAMPION:
			/*
			 * The CK_BARRIER_TOURNAMENT_CHAMPION waits until it wins the tournament; it then
			 * sets the final flag before the wakeup phase of the barrier.
			 */
			while (ck_pr_load_uint(&rounds[state->vpid][round].flag) != state->sense)
				ck_pr_stall();

			ck_pr_store_uint(rounds[state->vpid][round].opponent, state->sense);
			goto wakeup;
		case CK_BARRIER_TOURNAMENT_DROPOUT:
			/* NOTREACHED */
			break;
		case CK_BARRIER_TOURNAMENT_LOSER:
			/*
			 * CK_BARRIER_TOURNAMENT_LOSERs set the flags of their opponents and wait until
			 * their opponents release them after the tournament is over.
			 */
			ck_pr_store_uint(rounds[state->vpid][round].opponent, state->sense);
			while (ck_pr_load_uint(&rounds[state->vpid][round].flag) != state->sense)
				ck_pr_stall();

			goto wakeup;
		case CK_BARRIER_TOURNAMENT_WINNER:
			/*
			 * CK_BARRIER_TOURNAMENT_WINNERs wait until their current opponent sets their flag; they then
			 * continue to the next round of the tournament.
			 */
			while (ck_pr_load_uint(&rounds[state->vpid][round].flag) != state->sense)
				ck_pr_stall();
			break;
		}
	}

wakeup:
	for (round -= 1 ;; --round) {
		switch (rounds[state->vpid][round].role) {
		case CK_BARRIER_TOURNAMENT_BYE:
			break;
		case CK_BARRIER_TOURNAMENT_CHAMPION:
			/* NOTREACHED */
			break;
		case CK_BARRIER_TOURNAMENT_DROPOUT:
			goto leave;
			break;
		case CK_BARRIER_TOURNAMENT_LOSER:
			/* NOTREACHED */
			break;
		case CK_BARRIER_TOURNAMENT_WINNER:
			/*
			 * Winners inform their old opponents the tournament is over
			 * by setting their flags.
			 */
			ck_pr_store_uint(rounds[state->vpid][round].opponent, state->sense);
			break;
		}
	}

leave:
	ck_pr_fence_memory();
	state->sense = ~state->sense;
	return;
}