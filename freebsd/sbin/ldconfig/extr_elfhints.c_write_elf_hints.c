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
struct elfhints_hdr {int version; int strtab; scalar_t__ strsize; scalar_t__ dirlistlen; int /*<<< orphan*/  spare; scalar_t__ dirlist; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ELFHINTS_MAGIC ; 
 scalar_t__ EOF ; 
 int asprintf (char**,char*,char const*) ; 
 char** dirs ; 
 int /*<<< orphan*/  err (int,char*,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int fchmod (int,int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fwrite (struct elfhints_hdr*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mkstemp (char*) ; 
 int ndirs ; 
 scalar_t__ putc (char,int /*<<< orphan*/ *) ; 
 int rename (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
write_elf_hints(const char *hintsfile)
{
	struct elfhints_hdr	 hdr;
	char			*tempname;
	int			 fd;
	FILE			*fp;
	int			 i;

	if (asprintf(&tempname, "%s.XXXXXX", hintsfile) == -1)
		errx(1, "Out of memory");
	if ((fd = mkstemp(tempname)) ==  -1)
		err(1, "mkstemp(%s)", tempname);
	if (fchmod(fd, 0444) == -1)
		err(1, "fchmod(%s)", tempname);
	if ((fp = fdopen(fd, "wb")) == NULL)
		err(1, "fdopen(%s)", tempname);

	hdr.magic = ELFHINTS_MAGIC;
	hdr.version = 1;
	hdr.strtab = sizeof hdr;
	hdr.strsize = 0;
	hdr.dirlist = 0;
	memset(hdr.spare, 0, sizeof hdr.spare);

	/* Count up the size of the string table. */
	if (ndirs > 0) {
		hdr.strsize += strlen(dirs[0]);
		for (i = 1;  i < ndirs;  i++)
			hdr.strsize += 1 + strlen(dirs[i]);
	}
	hdr.dirlistlen = hdr.strsize;
	hdr.strsize++;	/* For the null terminator */

	/* Write the header. */
	if (fwrite(&hdr, 1, sizeof hdr, fp) != sizeof hdr)
		err(1, "%s: write error", tempname);
	/* Write the strings. */
	if (ndirs > 0) {
		if (fputs(dirs[0], fp) == EOF)
			err(1, "%s: write error", tempname);
		for (i = 1;  i < ndirs;  i++)
			if (fprintf(fp, ":%s", dirs[i]) < 0)
				err(1, "%s: write error", tempname);
	}
	if (putc('\0', fp) == EOF || fclose(fp) == EOF)
		err(1, "%s: write error", tempname);

	if (rename(tempname, hintsfile) == -1)
		err(1, "rename %s to %s", tempname, hintsfile);
	free(tempname);
}