#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct req {int dummy; } ;
struct TYPE_3__ {char** tblock; int count; scalar_t__ firstrec; scalar_t__ tapea; struct req* req; } ;

/* Variables and functions */
 int SLAVES ; 
 int TP_BSIZE ; 
 scalar_t__ blocksperfile ; 
 scalar_t__ cartridge ; 
 int density ; 
 int getpagesize () ; 
 scalar_t__ malloc (unsigned int) ; 
 char** nextblock ; 
 int ntrec ; 
 int reqsiz ; 
 TYPE_1__* slaves ; 
 TYPE_1__* slp ; 
 int tenths ; 
 int /*<<< orphan*/  unlimited ; 
 int writesize ; 

int
alloctape(void)
{
	int pgoff = getpagesize() - 1;
	char *buf;
	int i;

	writesize = ntrec * TP_BSIZE;
	reqsiz = (ntrec + 1) * sizeof(struct req);
	/*
	 * CDC 92181's and 92185's make 0.8" gaps in 1600-bpi start/stop mode
	 * (see DEC TU80 User's Guide).  The shorter gaps of 6250-bpi require
	 * repositioning after stopping, i.e, streaming mode, where the gap is
	 * variable, 0.30" to 0.45".  The gap is maximal when the tape stops.
	 */
	if (blocksperfile == 0 && !unlimited)
		tenths = writesize / density +
		    (cartridge ? 16 : density == 625 ? 5 : 8);
	/*
	 * Allocate tape buffer contiguous with the array of instruction
	 * packets, so flushtape() can write them together with one write().
	 * Align tape buffer on page boundary to speed up tape write().
	 */
	for (i = 0; i <= SLAVES; i++) {
		buf = (char *)
		    malloc((unsigned)(reqsiz + writesize + pgoff + TP_BSIZE));
		if (buf == NULL)
			return(0);
		slaves[i].tblock = (char (*)[TP_BSIZE])
		    (((long)&buf[ntrec + 1] + pgoff) &~ pgoff);
		slaves[i].req = (struct req *)slaves[i].tblock - ntrec - 1;
	}
	slp = &slaves[0];
	slp->count = 1;
	slp->tapea = 0;
	slp->firstrec = 0;
	nextblock = slp->tblock;
	return(1);
}