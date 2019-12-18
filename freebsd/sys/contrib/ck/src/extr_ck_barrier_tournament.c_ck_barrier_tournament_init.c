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
struct ck_barrier_tournament_round {scalar_t__ role; scalar_t__ flag; scalar_t__* opponent; } ;
struct ck_barrier_tournament {unsigned int size; int /*<<< orphan*/  rounds; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 scalar_t__ CK_BARRIER_TOURNAMENT_BYE ; 
 scalar_t__ CK_BARRIER_TOURNAMENT_CHAMPION ; 
 scalar_t__ CK_BARRIER_TOURNAMENT_DROPOUT ; 
 scalar_t__ CK_BARRIER_TOURNAMENT_LOSER ; 
 scalar_t__ CK_BARRIER_TOURNAMENT_WINNER ; 
 unsigned int ck_barrier_tournament_size (unsigned int) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (int /*<<< orphan*/ *,struct ck_barrier_tournament_round**) ; 
 int /*<<< orphan*/  ck_pr_store_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ck_barrier_tournament_init(struct ck_barrier_tournament *barrier,
    struct ck_barrier_tournament_round **rounds,
    unsigned int nthr)
{
	unsigned int i, k, size, twok, twokm1, imod2k;

	ck_pr_store_uint(&barrier->tid, 0);
	barrier->size = size = ck_barrier_tournament_size(nthr);

	for (i = 0; i < nthr; ++i) {
		/* The first role is always CK_BARRIER_TOURNAMENT_DROPOUT. */
		rounds[i][0].flag = 0;
		rounds[i][0].role = CK_BARRIER_TOURNAMENT_DROPOUT;
		for (k = 1, twok = 2, twokm1 = 1; k < size; ++k, twokm1 = twok, twok <<= 1) {
			rounds[i][k].flag = 0;

			imod2k = i & (twok - 1);
			if (imod2k == 0) {
				if ((i + twokm1 < nthr) && (twok < nthr))
					rounds[i][k].role = CK_BARRIER_TOURNAMENT_WINNER;
				else if (i + twokm1 >= nthr)
					rounds[i][k].role = CK_BARRIER_TOURNAMENT_BYE;
			}

			if (imod2k == twokm1)
				rounds[i][k].role = CK_BARRIER_TOURNAMENT_LOSER;
			else if ((i == 0) && (twok >= nthr))
				rounds[i][k].role = CK_BARRIER_TOURNAMENT_CHAMPION;

			if (rounds[i][k].role == CK_BARRIER_TOURNAMENT_LOSER)
				rounds[i][k].opponent = &rounds[i - twokm1][k].flag;
			else if (rounds[i][k].role == CK_BARRIER_TOURNAMENT_WINNER ||
				 rounds[i][k].role == CK_BARRIER_TOURNAMENT_CHAMPION)
				rounds[i][k].opponent = &rounds[i + twokm1][k].flag;
		}
	}

	ck_pr_store_ptr(&barrier->rounds, rounds);
	return;
}