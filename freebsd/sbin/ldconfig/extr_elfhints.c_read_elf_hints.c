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
struct stat {scalar_t__ st_size; } ;
struct elfhints_hdr {scalar_t__ magic; int version; int /*<<< orphan*/  dirlist; int /*<<< orphan*/  strtab; } ;

/* Variables and functions */
 scalar_t__ ELFHINTS_MAGIC ; 
 scalar_t__ ENOENT ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 scalar_t__ MAXFILESIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  add_dir (char const*,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 int fstat (int,struct stat*) ; 
 void* mmap (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
read_elf_hints(const char *hintsfile, int must_exist)
{
	int	 		 fd;
	struct stat		 s;
	void			*mapbase;
	struct elfhints_hdr	*hdr;
	char			*strtab;
	char			*dirlist;
	char			*p;

	if ((fd = open(hintsfile, O_RDONLY)) == -1) {
		if (errno == ENOENT && !must_exist)
			return;
		err(1, "Cannot open \"%s\"", hintsfile);
	}
	if (fstat(fd, &s) == -1)
		err(1, "Cannot stat \"%s\"", hintsfile);
	if (s.st_size > MAXFILESIZE)
		errx(1, "\"%s\" is unreasonably large", hintsfile);
	/*
	 * We use a read-write, private mapping so that we can null-terminate
	 * some strings in it without affecting the underlying file.
	 */
	mapbase = mmap(NULL, s.st_size, PROT_READ|PROT_WRITE,
	    MAP_PRIVATE, fd, 0);
	if (mapbase == MAP_FAILED)
		err(1, "Cannot mmap \"%s\"", hintsfile);
	close(fd);

	hdr = (struct elfhints_hdr *)mapbase;
	if (hdr->magic != ELFHINTS_MAGIC)
		errx(1, "\"%s\": invalid file format", hintsfile);
	if (hdr->version != 1)
		errx(1, "\"%s\": unrecognized file version (%d)", hintsfile,
		    hdr->version);

	strtab = (char *)mapbase + hdr->strtab;
	dirlist = strtab + hdr->dirlist;

	if (*dirlist != '\0')
		while ((p = strsep(&dirlist, ":")) != NULL)
			add_dir(hintsfile, p, 1);
}