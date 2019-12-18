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
struct symtableheader {long volno; size_t maxino; size_t entrytblsize; long stringsize; int /*<<< orphan*/  ntrec; int /*<<< orphan*/  dumpdate; int /*<<< orphan*/  dumptime; } ;
struct entry {char* e_name; scalar_t__ e_index; struct entry* e_next; struct entry* e_entries; struct entry* e_sibling; struct entry* e_links; struct entry* e_parent; int /*<<< orphan*/  e_namlen; } ;
typedef  size_t ino_t ;
struct TYPE_2__ {scalar_t__ e_index; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ Nflag ; 
 size_t UFS_WINO ; 
 scalar_t__ allocsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  dumpdate ; 
 int /*<<< orphan*/  dumptime ; 
 TYPE_1__** entry ; 
 size_t entrytblsize ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 struct entry* lookupino (size_t) ; 
 size_t maxino ; 
 int /*<<< orphan*/  memmove (struct entry*,struct entry*,long) ; 
 int /*<<< orphan*/  ntrec ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

void
dumpsymtable(char *filename, long checkpt)
{
	struct entry *ep, *tep;
	ino_t i;
	struct entry temp, *tentry;
	long mynum = 1, stroff = 0;
	FILE *fd;
	struct symtableheader hdr;

	vprintf(stdout, "Checkpointing the restore\n");
	if (Nflag)
		return;
	if ((fd = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "fopen: %s\n", strerror(errno));
		panic("cannot create save file %s for symbol table\n",
			filename);
		done(1);
	}
	clearerr(fd);
	/*
	 * Assign indices to each entry
	 * Write out the string entries
	 */
	for (i = UFS_WINO; i <= maxino; i++) {
		for (ep = lookupino(i); ep != NULL; ep = ep->e_links) {
			ep->e_index = mynum++;
			(void) fwrite(ep->e_name, sizeof(char),
			       (int)allocsize(ep->e_namlen), fd);
		}
	}
	/*
	 * Convert pointers to indexes, and output
	 */
	tep = &temp;
	stroff = 0;
	for (i = UFS_WINO; i <= maxino; i++) {
		for (ep = lookupino(i); ep != NULL; ep = ep->e_links) {
			memmove(tep, ep, (long)sizeof(struct entry));
			tep->e_name = (char *)stroff;
			stroff += allocsize(ep->e_namlen);
			tep->e_parent = (struct entry *)ep->e_parent->e_index;
			if (ep->e_links != NULL)
				tep->e_links =
					(struct entry *)ep->e_links->e_index;
			if (ep->e_sibling != NULL)
				tep->e_sibling =
					(struct entry *)ep->e_sibling->e_index;
			if (ep->e_entries != NULL)
				tep->e_entries =
					(struct entry *)ep->e_entries->e_index;
			if (ep->e_next != NULL)
				tep->e_next =
					(struct entry *)ep->e_next->e_index;
			(void) fwrite((char *)tep, sizeof(struct entry), 1, fd);
		}
	}
	/*
	 * Convert entry pointers to indexes, and output
	 */
	for (i = 0; i < entrytblsize; i++) {
		if (entry[i] == NULL)
			tentry = NULL;
		else
			tentry = (struct entry *)entry[i]->e_index;
		(void) fwrite((char *)&tentry, sizeof(struct entry *), 1, fd);
	}
	hdr.volno = checkpt;
	hdr.maxino = maxino;
	hdr.entrytblsize = entrytblsize;
	hdr.stringsize = stroff;
	hdr.dumptime = dumptime;
	hdr.dumpdate = dumpdate;
	hdr.ntrec = ntrec;
	(void) fwrite((char *)&hdr, sizeof(struct symtableheader), 1, fd);
	if (ferror(fd)) {
		fprintf(stderr, "fwrite: %s\n", strerror(errno));
		panic("output error to file %s writing symbol table\n",
			filename);
	}
	(void) fclose(fd);
}