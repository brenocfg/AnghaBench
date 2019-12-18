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
struct ttyoutq_block {int dummy; } ;
struct ttyoutq {scalar_t__ to_quota; scalar_t__ to_nblocks; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TTYOUTQ_DATASIZE ; 
 int /*<<< orphan*/  TTYOUTQ_INSERT_TAIL (struct ttyoutq*,struct ttyoutq_block*) ; 
 scalar_t__ howmany (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyoutq_zone ; 
 struct ttyoutq_block* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct ttyoutq_block*) ; 

int
ttyoutq_setsize(struct ttyoutq *to, struct tty *tp, size_t size)
{
	struct ttyoutq_block *tob;

	to->to_quota = howmany(size, TTYOUTQ_DATASIZE);

	while (to->to_quota > to->to_nblocks) {
		/*
		 * List is getting bigger.
		 * Add new blocks to the tail of the list.
		 *
		 * We must unlock the TTY temporarily, because we need
		 * to allocate memory. This won't be a problem, because
		 * in the worst case, another thread ends up here, which
		 * may cause us to allocate too many blocks, but this
		 * will be caught by the loop below.
		 */
		tty_unlock(tp);
		tob = uma_zalloc(ttyoutq_zone, M_WAITOK);
		tty_lock(tp);

		if (tty_gone(tp)) {
			uma_zfree(ttyoutq_zone, tob);
			return (ENXIO);
		}

		TTYOUTQ_INSERT_TAIL(to, tob);
	}
	return (0);
}