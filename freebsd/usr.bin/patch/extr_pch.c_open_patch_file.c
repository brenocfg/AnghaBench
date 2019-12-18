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
struct stat {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 char const* TMPPATNAME ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  buf_size ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int fwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_intuit_at (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  p_filesize ; 
 int /*<<< orphan*/  pfatal (char*,char const*) ; 
 int /*<<< orphan*/ * pfp ; 
 int /*<<< orphan*/  set_hunkmax () ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strEQ (char const*,char*) ; 

void
open_patch_file(const char *filename)
{
	struct stat filestat;
	int nr, nw;

	if (filename == NULL || *filename == '\0' || strEQ(filename, "-")) {
		pfp = fopen(TMPPATNAME, "w");
		if (pfp == NULL)
			pfatal("can't create %s", TMPPATNAME);
		while ((nr = fread(buf, 1, buf_size, stdin)) > 0) {
			nw = fwrite(buf, 1, nr, pfp);
			if (nr != nw)
				pfatal("write error to %s", TMPPATNAME);
		}
		if (ferror(pfp) || fclose(pfp))
			pfatal("can't write %s", TMPPATNAME);
		filename = TMPPATNAME;
	}
	pfp = fopen(filename, "r");
	if (pfp == NULL)
		pfatal("patch file %s not found", filename);
	if (fstat(fileno(pfp), &filestat))
		pfatal("can't stat %s", filename);
	p_filesize = filestat.st_size;
	next_intuit_at(0, 1L);	/* start at the beginning */
	set_hunkmax();
}