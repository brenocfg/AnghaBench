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
struct entry {int e_flags; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_2__ {scalar_t__ ino; void* action; } ;

/* Variables and functions */
 scalar_t__ Dflag ; 
 int EXTRACT ; 
 int NEW ; 
 void* SKIP ; 
 scalar_t__ UFS_ROOTINO ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  extractfile (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  getvol (long) ; 
 struct entry* lookupino (scalar_t__) ; 
 scalar_t__ lowerbnd (scalar_t__) ; 
 scalar_t__ maxino ; 
 char* myname (struct entry*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  skipdirs () ; 
 int /*<<< orphan*/  skipfile () ; 
 int /*<<< orphan*/  skipmaps () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ upperbnd (scalar_t__) ; 
 int volno ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

void
createfiles(void)
{
	ino_t first, next, last;
	struct entry *ep;
	long curvol;

	vprintf(stdout, "Extract requested files\n");
	curfile.action = SKIP;
	getvol((long)1);
	skipmaps();
	skipdirs();
	first = lowerbnd(UFS_ROOTINO);
	last = upperbnd(maxino - 1);
	for (;;) {
		curvol = volno;
		first = lowerbnd(first);
		last = upperbnd(last);
		/*
		 * Check to see if any files remain to be extracted
		 */
		if (first > last)
			return;
		if (Dflag) {
			if (curfile.ino == maxino)
				return;
			if((ep = lookupino(curfile.ino)) != NULL &&
			    (ep->e_flags & (NEW|EXTRACT))) {
				goto justgetit;
			} else {
				skipfile();
				continue;
			}
		}
		/*
		 * Reject any volumes with inodes greater than the last
		 * one needed, so that we can quickly skip backwards to
		 * a volume containing useful inodes. We can't do this
		 * if there are no further volumes available (curfile.ino
		 * >= maxino) or if we are already at the first tape.
		 */
		if (curfile.ino > last && curfile.ino < maxino && volno > 1) {
			curfile.action = SKIP;
			getvol((long)0);
			skipmaps();
			skipdirs();
			continue;
		}
		/*
		 * Decide on the next inode needed.
		 * Skip across the inodes until it is found
		 * or a volume change is encountered
		 */
		if (curfile.ino < maxino) {
			next = lowerbnd(curfile.ino);
			while (next > curfile.ino && volno == curvol)
				skipfile();
			if (volno != curvol) {
				skipmaps();
				skipdirs();
				continue;
			}
		} else {
			/*
			 * No further volumes or inodes available. Set
			 * `next' to the first inode, so that a warning
			 * is emitted below for each missing file.
			 */
			next = first;
		}
		/*
		 * If the current inode is greater than the one we were
		 * looking for then we missed the one we were looking for.
		 * Since we only attempt to extract files listed in the
		 * dump map, the lost files must have been due to a tape
		 * read error, or a file that was removed while the dump
		 * was in progress. Thus we report all requested files
		 * between the one we were looking for, and the one we
		 * found as missing, and delete their request flags.
		 */
		while (next < curfile.ino) {
			ep = lookupino(next);
			if (ep == NULL)
				panic("corrupted symbol table\n");
			fprintf(stderr, "%s: not found on tape\n", myname(ep));
			ep->e_flags &= ~NEW;
			next = lowerbnd(next);
		}
		/*
		 * The current inode is the one that we are looking for,
		 * so extract it per its requested name.
		 */
		if (next == curfile.ino && next <= last) {
			ep = lookupino(next);
			if (ep == NULL)
				panic("corrupted symbol table\n");
justgetit:
			(void) extractfile(myname(ep));
			ep->e_flags &= ~NEW;
			if (volno != curvol)
				skipmaps();
		}
	}
}