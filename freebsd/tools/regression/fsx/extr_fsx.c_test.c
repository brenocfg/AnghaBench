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

/* Variables and functions */
 int /*<<< orphan*/  check_size () ; 
 int closeopen ; 
 int closeprob ; 
 int debug ; 
 scalar_t__ debugstart ; 
 int /*<<< orphan*/  docloseopen () ; 
 int /*<<< orphan*/  doinvl () ; 
 int /*<<< orphan*/  domapread (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  domapwrite (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  doread (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dotruncate (unsigned long) ; 
 int /*<<< orphan*/  dowrite (unsigned long,unsigned long) ; 
 long file_size ; 
 int invl ; 
 int invlprob ; 
 scalar_t__ lite ; 
 int /*<<< orphan*/  mapped_reads ; 
 int mapped_writes ; 
 unsigned long maxfilelen ; 
 int maxoplen ; 
 int /*<<< orphan*/  prt (char*,scalar_t__) ; 
 int /*<<< orphan*/  quiet ; 
 int random () ; 
 scalar_t__ randomoplen ; 
 scalar_t__ simulatedopcount ; 
 scalar_t__ sizechecks ; 
 scalar_t__ style ; 
 scalar_t__ testcalls ; 
 int /*<<< orphan*/  writefileimage () ; 

void
test(void)
{
	unsigned long	offset;
	unsigned long	size = maxoplen;
	unsigned long	rv = random();
	unsigned long	op = rv % (3 + !lite + mapped_writes);

	/* turn off the map read if necessary */

	if (op == 2 && !mapped_reads)
	    op = 0;

	if (simulatedopcount > 0 && testcalls == simulatedopcount)
		writefileimage();

	testcalls++;

	if (closeprob)
		closeopen = (rv >> 3) < (1 << 28) / closeprob;
	if (invlprob)
		invl = (rv >> 3) < (1 << 28) / invlprob;

	if (debugstart > 0 && testcalls >= debugstart)
		debug = 1;

	if (!quiet && testcalls < simulatedopcount && testcalls % 100000 == 0)
		prt("%lu...\n", testcalls);

	/*
	 * READ:	op = 0
	 * WRITE:	op = 1
	 * MAPREAD:     op = 2
	 * TRUNCATE:	op = 3
	 * MAPWRITE:    op = 3 or 4
	 */
	if (lite ? 0 : op == 3 && style == 0) /* vanilla truncate? */
		dotruncate(random() % maxfilelen);
	else {
		if (randomoplen)
			size = random() % (maxoplen+1);
		if (lite ? 0 : op == 3)
			dotruncate(size);
		else {
			offset = random();
			if (op == 1 || op == (lite ? 3 : 4)) {
				offset %= maxfilelen;
				if (offset + size > maxfilelen)
					size = maxfilelen - offset;
				if (op != 1)
					domapwrite(offset, size);
				else
					dowrite(offset, size);
			} else {
				if (file_size)
					offset %= file_size;
				else
					offset = 0;
				if (offset + size > file_size)
					size = file_size - offset;
				if (op != 0)
					domapread(offset, size);
				else
					doread(offset, size);
			}
		}
	}
	if (sizechecks && testcalls > simulatedopcount)
		check_size();
	if (invl)
		doinvl();
	if (closeopen)
		docloseopen();
}