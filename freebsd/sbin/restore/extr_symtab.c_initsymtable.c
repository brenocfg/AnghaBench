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
struct symtableheader {int maxino; int entrytblsize; int stringsize; int /*<<< orphan*/  volno; int /*<<< orphan*/  ntrec; int /*<<< orphan*/  dumpdate; int /*<<< orphan*/  dumptime; } ;
struct stat {int st_size; } ;
struct entry {char* e_name; struct entry* e_next; struct entry* e_entries; struct entry* e_links; struct entry* e_sibling; struct entry* e_parent; int /*<<< orphan*/  e_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int HASHFACTOR ; 
 int /*<<< orphan*/  NEW ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SKIP ; 
 int /*<<< orphan*/  UFS_ROOTINO ; 
 struct entry* addentry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bflag ; 
 void* calloc (int,unsigned int) ; 
 int /*<<< orphan*/  close (int) ; 
 int command ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  dumpdate ; 
 int /*<<< orphan*/  dumptime ; 
 struct entry** entry ; 
 int entrytblsize ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  getvol (int /*<<< orphan*/ ) ; 
 int maxino ; 
 int /*<<< orphan*/  newtapebuf (int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

void
initsymtable(char *filename)
{
	char *base;
	long tblsize;
	struct entry *ep;
	struct entry *baseep, *lep;
	struct symtableheader hdr;
	struct stat stbuf;
	long i;
	int fd;

	vprintf(stdout, "Initialize symbol table.\n");
	if (filename == NULL) {
		entrytblsize = maxino / HASHFACTOR;
		entry = calloc((unsigned)entrytblsize, sizeof(struct entry *));
		if (entry == NULL)
			panic("no memory for entry table\n");
		ep = addentry(".", UFS_ROOTINO, NODE);
		ep->e_flags |= NEW;
		return;
	}
	if ((fd = open(filename, O_RDONLY, 0)) < 0) {
		fprintf(stderr, "open: %s\n", strerror(errno));
		panic("cannot open symbol table file %s\n", filename);
	}
	if (fstat(fd, &stbuf) < 0) {
		fprintf(stderr, "stat: %s\n", strerror(errno));
		panic("cannot stat symbol table file %s\n", filename);
	}
	tblsize = stbuf.st_size - sizeof(struct symtableheader);
	base = calloc(sizeof(char), (unsigned)tblsize);
	if (base == NULL)
		panic("cannot allocate space for symbol table\n");
	if (read(fd, base, (int)tblsize) < 0 ||
	    read(fd, (char *)&hdr, sizeof(struct symtableheader)) < 0) {
		fprintf(stderr, "read: %s\n", strerror(errno));
		panic("cannot read symbol table file %s\n", filename);
	}
	(void)close(fd);
	switch (command) {
	case 'r':
		/*
		 * For normal continuation, insure that we are using
		 * the next incremental tape
		 */
		if (hdr.dumpdate != dumptime) {
			if (hdr.dumpdate < dumptime)
				fprintf(stderr, "Incremental tape too low\n");
			else
				fprintf(stderr, "Incremental tape too high\n");
			done(1);
		}
		break;
	case 'R':
		/*
		 * For restart, insure that we are using the same tape
		 */
		curfile.action = SKIP;
		dumptime = hdr.dumptime;
		dumpdate = hdr.dumpdate;
		if (!bflag)
			newtapebuf(hdr.ntrec);
		getvol(hdr.volno);
		break;
	default:
		panic("initsymtable called from command %c\n", command);
		break;
	}
	maxino = hdr.maxino;
	entrytblsize = hdr.entrytblsize;
	entry = (struct entry **)
		(base + tblsize - (entrytblsize * sizeof(struct entry *)));
	baseep = (struct entry *)(base + hdr.stringsize - sizeof(struct entry));
	lep = (struct entry *)entry;
	for (i = 0; i < entrytblsize; i++) {
		if (entry[i] == NULL)
			continue;
		entry[i] = &baseep[(long)entry[i]];
	}
	for (ep = &baseep[1]; ep < lep; ep++) {
		ep->e_name = base + (long)ep->e_name;
		ep->e_parent = &baseep[(long)ep->e_parent];
		if (ep->e_sibling != NULL)
			ep->e_sibling = &baseep[(long)ep->e_sibling];
		if (ep->e_links != NULL)
			ep->e_links = &baseep[(long)ep->e_links];
		if (ep->e_entries != NULL)
			ep->e_entries = &baseep[(long)ep->e_entries];
		if (ep->e_next != NULL)
			ep->e_next = &baseep[(long)ep->e_next];
	}
}