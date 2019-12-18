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
struct shlib_list {struct shlib_list* next; int /*<<< orphan*/  ndewey; int /*<<< orphan*/  dewey; void* path; void* name; } ;
struct hints_header {scalar_t__ hh_version; long hh_ehints; int hh_strtab; int hh_dirlist; int hh_nbucket; int hh_hashtab; long hh_strtab_sz; scalar_t__ hh_magic; } ;
struct hints_bucket {long hi_namex; long hi_pathx; int /*<<< orphan*/  hi_ndewey; int /*<<< orphan*/  hi_dewey; } ;

/* Variables and functions */
 scalar_t__ HH_BADMAG (struct hints_header) ; 
 scalar_t__ LD_HINTS_VERSION_1 ; 
 scalar_t__ LD_HINTS_VERSION_2 ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 long PAGE_SIZE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  add_search_path (char*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct hints_bucket*) ; 
 int /*<<< orphan*/  hints_file ; 
 struct hints_bucket* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct hints_bucket*,char*,int) ; 
 void* mmap (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,long) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rescan ; 
 struct shlib_list** shlib_tail ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,long,...) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static int
readhints(void)
{
	int			fd;
	void			*addr;
	long			fsize;
	long			msize;
	struct hints_header	*hdr;
	struct hints_bucket	*blist;
	char			*strtab;
	struct shlib_list	*shp;
	int			i;

	if ((fd = open(hints_file, O_RDONLY, 0)) == -1) {
		warn("%s", hints_file);
		return -1;
	}

	msize = PAGE_SIZE;
	addr = mmap(0, msize, PROT_READ, MAP_PRIVATE, fd, 0);

	if (addr == MAP_FAILED) {
		warn("%s", hints_file);
		return -1;
	}

	hdr = (struct hints_header *)addr;
	if (HH_BADMAG(*hdr)) {
		warnx("%s: bad magic: %lo", hints_file,
			(unsigned long)hdr->hh_magic);
		return -1;
	}

	if (hdr->hh_version != LD_HINTS_VERSION_1 &&
	    hdr->hh_version != LD_HINTS_VERSION_2) {
		warnx("unsupported version: %ld", (long)hdr->hh_version);
		return -1;
	}

	if (hdr->hh_ehints > msize) {
		fsize = hdr->hh_ehints;
		munmap(addr, msize);
		addr = mmap(0, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
		if (addr == MAP_FAILED) {
			warn("%s", hints_file);
			return -1;
		}
		hdr = (struct hints_header *)addr;
	}
	close(fd);

	strtab = (char *)addr + hdr->hh_strtab;

	if (hdr->hh_version >= LD_HINTS_VERSION_2)
		add_search_path(strtab + hdr->hh_dirlist);
	else if (rescan)
		errx(1, "%s too old and does not contain the search path",
			hints_file);

	if (rescan)
		return 0;

	blist = malloc(sizeof(*blist) * hdr->hh_nbucket);
	if (blist == NULL)
		err(1, "readhints");
	memcpy(blist, (char *)addr + hdr->hh_hashtab,
		sizeof(*blist) * hdr->hh_nbucket);


	for (i = 0; i < hdr->hh_nbucket; i++) {
		struct hints_bucket	*bp = &blist[i];

		/* Sanity check */
		if (bp->hi_namex >= hdr->hh_strtab_sz) {
			warnx("bad name index: %#x", bp->hi_namex);
			free(blist);
			return -1;
		}
		if (bp->hi_pathx >= hdr->hh_strtab_sz) {
			warnx("bad path index: %#x", bp->hi_pathx);
			free(blist);
			return -1;
		}

		/* Allocate new list element */
		shp = (struct shlib_list *)xmalloc(sizeof *shp);
		shp->name = strdup(strtab + bp->hi_namex);
		shp->path = strdup(strtab + bp->hi_pathx);
		bcopy(bp->hi_dewey, shp->dewey, sizeof(shp->dewey));
		shp->ndewey = bp->hi_ndewey;
		shp->next = NULL;

		*shlib_tail = shp;
		shlib_tail = &shp->next;
	}

	free(blist);
	return 0;
}