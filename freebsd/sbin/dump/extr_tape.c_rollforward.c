#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union u_spcl {int dummy; } u_spcl ;
struct slave {int sent; int /*<<< orphan*/  fd; scalar_t__* tblock; struct req* req; void* tapea; } ;
struct req {scalar_t__ count; scalar_t__ dblk; } ;
typedef  void* int64_t ;
struct TYPE_2__ {void* c_tapea; } ;

/* Variables and functions */
 int DEV_BSIZE ; 
 size_t SLAVES ; 
 int TP_BSIZE ; 
 int atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dumpabort (int /*<<< orphan*/ ) ; 
 void* lastspclrec ; 
 scalar_t__* nextblock ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  quit (char*) ; 
 int /*<<< orphan*/  read ; 
 struct slave* slaves ; 
 struct slave* slp ; 
 TYPE_1__ spcl ; 
 int /*<<< orphan*/  startnewtape (int /*<<< orphan*/ ) ; 
 int trecno ; 
 int /*<<< orphan*/  write ; 
 int writesize ; 

void
rollforward(void)
{
	struct req *p, *q, *prev;
	struct slave *tslp;
	int i, size, got;
	int64_t savedtapea;
	union u_spcl *ntb, *otb;
	tslp = &slaves[SLAVES];
	ntb = (union u_spcl *)tslp->tblock[1];

	/*
	 * Each of the N slaves should have requests that need to
	 * be replayed on the next tape.  Use the extra slave buffers
	 * (slaves[SLAVES]) to construct request lists to be sent to
	 * each slave in turn.
	 */
	for (i = 0; i < SLAVES; i++) {
		q = &tslp->req[1];
		otb = (union u_spcl *)slp->tblock;

		/*
		 * For each request in the current slave, copy it to tslp.
		 */

		prev = NULL;
		for (p = slp->req; p->count > 0; p += p->count) {
			*q = *p;
			if (p->dblk == 0)
				*ntb++ = *otb++; /* copy the datablock also */
			prev = q;
			q += q->count;
		}
		if (prev == NULL)
			quit("rollforward: protocol botch");
		if (prev->dblk != 0)
			prev->count -= 1;
		else
			ntb--;
		q -= 1;
		q->count = 0;
		q = &tslp->req[0];
		if (i == 0) {
			q->dblk = 0;
			q->count = 1;
			trecno = 0;
			nextblock = tslp->tblock;
			savedtapea = spcl.c_tapea;
			spcl.c_tapea = slp->tapea;
			startnewtape(0);
			spcl.c_tapea = savedtapea;
			lastspclrec = savedtapea - 1;
		}
		size = (char *)ntb - (char *)q;
		if (atomic(write, slp->fd, (char *)q, size) != size) {
			perror("  DUMP: error writing command pipe");
			dumpabort(0);
		}
		slp->sent = 1;
		if (++slp >= &slaves[SLAVES])
			slp = &slaves[0];

		q->count = 1;

		if (prev->dblk != 0) {
			/*
			 * If the last one was a disk block, make the
			 * first of this one be the last bit of that disk
			 * block...
			 */
			q->dblk = prev->dblk +
				prev->count * (TP_BSIZE / DEV_BSIZE);
			ntb = (union u_spcl *)tslp->tblock;
		} else {
			/*
			 * It wasn't a disk block.  Copy the data to its
			 * new location in the buffer.
			 */
			q->dblk = 0;
			*((union u_spcl *)tslp->tblock) = *ntb;
			ntb = (union u_spcl *)tslp->tblock[1];
		}
	}
	slp->req[0] = *q;
	nextblock = slp->tblock;
	if (q->dblk == 0)
		nextblock++;
	trecno = 1;

	/*
	 * Clear the first slaves' response.  One hopes that it
	 * worked ok, otherwise the tape is much too short!
	 */
	if (slp->sent) {
		if (atomic(read, slp->fd, (char *)&got, sizeof got)
		    != sizeof got) {
			perror("  DUMP: error reading command pipe in master");
			dumpabort(0);
		}
		slp->sent = 0;

		if (got != writesize) {
			quit("EOT detected at start of the tape!\n");
		}
	}
}