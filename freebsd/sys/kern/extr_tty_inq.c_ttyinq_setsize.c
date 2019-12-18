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
struct ttyinq_block {int dummy; } ;
struct ttyinq {scalar_t__ ti_quota; scalar_t__ ti_nblocks; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TTYINQ_DATASIZE ; 
 int /*<<< orphan*/  TTYINQ_INSERT_TAIL (struct ttyinq*,struct ttyinq_block*) ; 
 scalar_t__ howmany (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyinq_zone ; 
 struct ttyinq_block* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct ttyinq_block*) ; 

int 
ttyinq_setsize(struct ttyinq *ti, struct tty *tp, size_t size)
{
	struct ttyinq_block *tib;

	ti->ti_quota = howmany(size, TTYINQ_DATASIZE);

	while (ti->ti_quota > ti->ti_nblocks) {
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
		tib = uma_zalloc(ttyinq_zone, M_WAITOK);
		tty_lock(tp);

		if (tty_gone(tp)) {
			uma_zfree(ttyinq_zone, tib);
			return (ENXIO);
		}

		TTYINQ_INSERT_TAIL(ti, tib);
	}
	return (0);
}