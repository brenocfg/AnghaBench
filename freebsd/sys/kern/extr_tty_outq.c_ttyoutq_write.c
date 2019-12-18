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
struct ttyoutq_block {scalar_t__ tob_data; struct ttyoutq_block* tob_next; } ;
struct ttyoutq {unsigned int to_end; scalar_t__ to_begin; struct ttyoutq_block* to_lastblock; struct ttyoutq_block* to_firstblock; } ;

/* Variables and functions */
 size_t MIN (size_t,unsigned int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 unsigned int TTYOUTQ_DATASIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 

size_t
ttyoutq_write(struct ttyoutq *to, const void *buf, size_t nbytes)
{
	const char *cbuf = buf;
	struct ttyoutq_block *tob;
	unsigned int boff;
	size_t l;

	while (nbytes > 0) {
		boff = to->to_end % TTYOUTQ_DATASIZE;

		if (to->to_end == 0) {
			/* First time we're being used or drained. */
			MPASS(to->to_begin == 0);
			tob = to->to_firstblock;
			if (tob == NULL) {
				/* Queue has no blocks. */
				break;
			}
			to->to_lastblock = tob;
		} else if (boff == 0) {
			/* We reached the end of this block on last write. */
			tob = to->to_lastblock->tob_next;
			if (tob == NULL) {
				/* We've reached the watermark. */
				break;
			}
			to->to_lastblock = tob;
		} else {
			tob = to->to_lastblock;
		}

		/* Don't copy more than was requested. */
		l = MIN(nbytes, TTYOUTQ_DATASIZE - boff);
		MPASS(l > 0);
		memcpy(tob->tob_data + boff, cbuf, l);

		cbuf += l;
		nbytes -= l;
		to->to_end += l;
	}

	return (cbuf - (const char *)buf);
}