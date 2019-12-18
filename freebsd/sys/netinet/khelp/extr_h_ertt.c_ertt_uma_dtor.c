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
struct txseginfo {int dummy; } ;
struct ertt {int /*<<< orphan*/  txsegi_q; } ;

/* Variables and functions */
 struct txseginfo* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct txseginfo* TAILQ_NEXT (struct txseginfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txsegi_lnk ; 
 int /*<<< orphan*/  txseginfo_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct txseginfo*) ; 

__attribute__((used)) static void
ertt_uma_dtor(void *mem, int size, void *arg)
{
	struct ertt *e_t;
	struct txseginfo *n_txsi, *txsi;

	e_t = mem;
	txsi = TAILQ_FIRST(&e_t->txsegi_q);
	while (txsi != NULL) {
		n_txsi = TAILQ_NEXT(txsi, txsegi_lnk);
		uma_zfree(txseginfo_zone, txsi);
		txsi = n_txsi;
	}
}