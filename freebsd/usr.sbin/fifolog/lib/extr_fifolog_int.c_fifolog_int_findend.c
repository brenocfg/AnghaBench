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
struct fifolog_file {int logsize; int /*<<< orphan*/  recbuf; } ;
typedef  unsigned int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 unsigned int be32dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifolog_int_file_assert (struct fifolog_file const*) ; 
 int fifolog_int_read (struct fifolog_file const*,unsigned int) ; 

const char *
fifolog_int_findend(const struct fifolog_file *ff, off_t *last)
{
	off_t o, s;
	int e;
	unsigned seq0, seq;

	fifolog_int_file_assert(ff);

	o = 0;
	e = fifolog_int_read(ff, o);
	if (e)
		return("Read error, first record");

	seq0 = be32dec(ff->recbuf);

	/* If the first records sequence is zero, the fifolog is empty */
	if (seq0 == 0) {
		*last = o;
		return (NULL);
	}

	/* Do a binary search for a discontinuity in the sequence numbers */
	s = ff->logsize / 2;
	do {
		e = fifolog_int_read(ff, o + s);
		if (e)
			return ("Read error while searching");
		seq = be32dec(ff->recbuf);
		if (seq == seq0 + s) {
			o += s;
			seq0 = seq;
		}
		s /= 2;
		assert(o < ff->logsize);
	} while (s > 0);

	*last = o;
	return (NULL);
}