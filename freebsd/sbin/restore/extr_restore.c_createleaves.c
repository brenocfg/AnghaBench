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
typedef  int /*<<< orphan*/  uintmax_t ;
struct entry {int e_flags; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_2__ {scalar_t__ ino; } ;

/* Variables and functions */
 int EXTRACT ; 
 int NEW ; 
 int REMOVED ; 
 scalar_t__ UFS_ROOTINO ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 char command ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  dumpsymtable (char*,long) ; 
 int /*<<< orphan*/  extractfile (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 struct entry* lookupino (scalar_t__) ; 
 scalar_t__ lowerbnd (scalar_t__) ; 
 scalar_t__ maxino ; 
 char* myname (struct entry*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  removeleaf (struct entry*) ; 
 int /*<<< orphan*/  skipfile () ; 
 int /*<<< orphan*/  skipmaps () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 long volno ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

void
createleaves(char *symtabfile)
{
	struct entry *ep;
	ino_t first;
	long curvol;

	if (command == 'R') {
		vprintf(stdout, "Continue extraction of new leaves\n");
	} else {
		vprintf(stdout, "Extract new leaves.\n");
		dumpsymtable(symtabfile, volno);
	}
	first = lowerbnd(UFS_ROOTINO);
	curvol = volno;
	while (curfile.ino < maxino) {
		first = lowerbnd(first);
		/*
		 * If the next available file is not the one which we
		 * expect then we have missed one or more files. Since
		 * we do not request files that were not on the tape,
		 * the lost files must have been due to a tape read error,
		 * or a file that was removed while the dump was in progress.
		 */
		while (first < curfile.ino) {
			ep = lookupino(first);
			if (ep == NULL)
				panic("%ju: bad first\n", (uintmax_t)first);
			fprintf(stderr, "%s: not found on tape\n", myname(ep));
			ep->e_flags &= ~(NEW|EXTRACT);
			first = lowerbnd(first);
		}
		/*
		 * If we find files on the tape that have no corresponding
		 * directory entries, then we must have found a file that
		 * was created while the dump was in progress. Since we have
		 * no name for it, we discard it knowing that it will be
		 * on the next incremental tape.
		 */
		if (first != curfile.ino) {
			fprintf(stderr, "expected next file %ju, got %ju\n",
			    (uintmax_t)first, (uintmax_t)curfile.ino);
			skipfile();
			goto next;
		}
		ep = lookupino(curfile.ino);
		if (ep == NULL)
			panic("unknown file on tape\n");
		if ((ep->e_flags & (NEW|EXTRACT)) == 0)
			badentry(ep, "unexpected file on tape");
		/*
		 * If the file is to be extracted, then the old file must
		 * be removed since its type may change from one leaf type
		 * to another (e.g. "file" to "character special").
		 */
		if ((ep->e_flags & EXTRACT) != 0) {
			removeleaf(ep);
			ep->e_flags &= ~REMOVED;
		}
		(void) extractfile(myname(ep));
		ep->e_flags &= ~(NEW|EXTRACT);
		/*
		 * We checkpoint the restore after every tape reel, so
		 * as to simplify the amount of work required by the
		 * 'R' command.
		 */
	next:
		if (curvol != volno) {
			dumpsymtable(symtabfile, volno);
			skipmaps();
			curvol = volno;
		}
	}
}