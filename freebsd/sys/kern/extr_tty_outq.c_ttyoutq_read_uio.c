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
struct uio {scalar_t__ uio_resid; } ;
struct ttyoutq_block {char* tob_data; } ;
struct ttyoutq {size_t to_begin; size_t to_end; struct ttyoutq_block* to_firstblock; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 size_t TTYOUTQ_DATASIZE ; 
 int /*<<< orphan*/  TTYOUTQ_RECYCLE (struct ttyoutq*,struct ttyoutq_block*) ; 
 int /*<<< orphan*/  TTYOUTQ_REMOVE_HEAD (struct ttyoutq*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int uiomove (char*,size_t,struct uio*) ; 

int
ttyoutq_read_uio(struct ttyoutq *to, struct tty *tp, struct uio *uio)
{

	while (uio->uio_resid > 0) {
		int error;
		struct ttyoutq_block *tob;
		size_t cbegin, cend, clen;

		/* See if there still is data. */
		if (to->to_begin == to->to_end)
			return (0);
		tob = to->to_firstblock;
		if (tob == NULL)
			return (0);

		/*
		 * The end address should be the lowest of these three:
		 * - The write pointer
		 * - The blocksize - we can't read beyond the block
		 * - The end address if we could perform the full read
		 */
		cbegin = to->to_begin;
		cend = MIN(MIN(to->to_end, to->to_begin + uio->uio_resid),
		    TTYOUTQ_DATASIZE);
		clen = cend - cbegin;

		/*
		 * We can prevent buffering in some cases:
		 * - We need to read the block until the end.
		 * - We don't need to read the block until the end, but
		 *   there is no data beyond it, which allows us to move
		 *   the write pointer to a new block.
		 */
		if (cend == TTYOUTQ_DATASIZE || cend == to->to_end) {
			/*
			 * Fast path: zero copy. Remove the first block,
			 * so we can unlock the TTY temporarily.
			 */
			TTYOUTQ_REMOVE_HEAD(to);
			to->to_begin = 0;
			if (to->to_end <= TTYOUTQ_DATASIZE)
				to->to_end = 0;
			else
				to->to_end -= TTYOUTQ_DATASIZE;

			/* Temporary unlock and copy the data to userspace. */
			tty_unlock(tp);
			error = uiomove(tob->tob_data + cbegin, clen, uio);
			tty_lock(tp);

			/* Block can now be readded to the list. */
			TTYOUTQ_RECYCLE(to, tob);
		} else {
			char ob[TTYOUTQ_DATASIZE - 1];

			/*
			 * Slow path: store data in a temporary buffer.
			 */
			memcpy(ob, tob->tob_data + cbegin, clen);
			to->to_begin += clen;
			MPASS(to->to_begin < TTYOUTQ_DATASIZE);

			/* Temporary unlock and copy the data to userspace. */
			tty_unlock(tp);
			error = uiomove(ob, clen, uio);
			tty_lock(tp);
		}

		if (error != 0)
			return (error);
	}

	return (0);
}