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
struct fifolog_file {scalar_t__ logsize; int* recbuf; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int FIFOLOG_FLG_SYNC ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int be32dec (int*) ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int fifolog_int_read (struct fifolog_file const*,scalar_t__) ; 

__attribute__((used)) static int
fifolog_reader_findsync(const struct fifolog_file *ff, off_t *o)
{
	int e;
	unsigned seq, seqs;

	assert(*o < ff->logsize);
	e = fifolog_int_read(ff, *o);
	if (e)
		err(1, "Read error (%d) while looking for SYNC", e);
	seq = be32dec(ff->recbuf);
	if (*o == 0 && seq == 0)
		return (0);

	if (ff->recbuf[4] & FIFOLOG_FLG_SYNC)
		return (1);		/* That was easy... */
	while(1) {
		assert(*o < ff->logsize);
		(*o)++;
		seq++;
		if (*o == ff->logsize)
			return (2);	/* wraparound */
		e = fifolog_int_read(ff, *o);
		if (e)
			err(1, "Read error (%d) while looking for SYNC", e);
		seqs = be32dec(ff->recbuf);
		if (seqs != seq)
			return (3);		/* End of log */
		if (ff->recbuf[4] & FIFOLOG_FLG_SYNC)
			return (1);		/* Bingo! */
	}
}