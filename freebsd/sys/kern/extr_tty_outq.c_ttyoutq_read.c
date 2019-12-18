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
struct ttyoutq_block {scalar_t__ tob_data; } ;
struct ttyoutq {size_t to_begin; size_t to_end; struct ttyoutq_block* to_firstblock; } ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 size_t TTYOUTQ_DATASIZE ; 
 int /*<<< orphan*/  TTYOUTQ_RECYCLE (struct ttyoutq*,struct ttyoutq_block*) ; 
 int /*<<< orphan*/  TTYOUTQ_REMOVE_HEAD (struct ttyoutq*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 

size_t
ttyoutq_read(struct ttyoutq *to, void *buf, size_t len)
{
	char *cbuf = buf;

	while (len > 0) {
		struct ttyoutq_block *tob;
		size_t cbegin, cend, clen;

		/* See if there still is data. */
		if (to->to_begin == to->to_end)
			break;
		tob = to->to_firstblock;
		if (tob == NULL)
			break;

		/*
		 * The end address should be the lowest of these three:
		 * - The write pointer
		 * - The blocksize - we can't read beyond the block
		 * - The end address if we could perform the full read
		 */
		cbegin = to->to_begin;
		cend = MIN(MIN(to->to_end, to->to_begin + len),
		    TTYOUTQ_DATASIZE);
		clen = cend - cbegin;

		/* Copy the data out of the buffers. */
		memcpy(cbuf, tob->tob_data + cbegin, clen);
		cbuf += clen;
		len -= clen;

		if (cend == to->to_end) {
			/* Read the complete queue. */
			to->to_begin = 0;
			to->to_end = 0;
		} else if (cend == TTYOUTQ_DATASIZE) {
			/* Read the block until the end. */
			TTYOUTQ_REMOVE_HEAD(to);
			to->to_begin = 0;
			to->to_end -= TTYOUTQ_DATASIZE;
			TTYOUTQ_RECYCLE(to, tob);
		} else {
			/* Read the block partially. */
			to->to_begin += clen;
		}
	}

	return (cbuf - (char *)buf);
}