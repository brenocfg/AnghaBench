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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct file {int fd; int binary; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ BINFILE_TEXT ; 
 scalar_t__ FILE_MMAP ; 
 scalar_t__ FILE_STDIO ; 
 int /*<<< orphan*/  MADV_SEQUENTIAL ; 
 int /*<<< orphan*/ * MAP_FAILED ; 
 int MAP_NOCORE ; 
 int MAP_NOSYNC ; 
 int MAP_PREFAULT_READ ; 
 int MAP_PRIVATE ; 
 int MAXBUFSIZ ; 
 scalar_t__ OFF_MAX ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ binbehave ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/ * bufpos ; 
 scalar_t__ bufrem ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ filebehave ; 
 char fileeol ; 
 int /*<<< orphan*/  free (struct file*) ; 
 scalar_t__ fsiz ; 
 int fstat (int,struct stat*) ; 
 void* grep_malloc (int) ; 
 scalar_t__ grep_refill (struct file*) ; 
 int lbflag ; 
 int /*<<< orphan*/  madvise (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ *,char,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

struct file *
grep_open(const char *path)
{
	struct file *f;

	f = grep_malloc(sizeof *f);
	memset(f, 0, sizeof *f);
	if (path == NULL) {
		/* Processing stdin implies --line-buffered. */
		lbflag = true;
		f->fd = STDIN_FILENO;
	} else if ((f->fd = open(path, O_RDONLY)) == -1)
		goto error1;

	if (filebehave == FILE_MMAP) {
		struct stat st;

		if ((fstat(f->fd, &st) == -1) || (st.st_size > OFF_MAX) ||
		    (!S_ISREG(st.st_mode)))
			filebehave = FILE_STDIO;
		else {
			int flags = MAP_PRIVATE | MAP_NOCORE | MAP_NOSYNC;
#ifdef MAP_PREFAULT_READ
			flags |= MAP_PREFAULT_READ;
#endif
			fsiz = st.st_size;
			buffer = mmap(NULL, fsiz, PROT_READ, flags,
			     f->fd, (off_t)0);
			if (buffer == MAP_FAILED)
				filebehave = FILE_STDIO;
			else {
				bufrem = st.st_size;
				bufpos = buffer;
				madvise(buffer, st.st_size, MADV_SEQUENTIAL);
			}
		}
	}

	if ((buffer == NULL) || (buffer == MAP_FAILED))
		buffer = grep_malloc(MAXBUFSIZ);

	/* Fill read buffer, also catches errors early */
	if (bufrem == 0 && grep_refill(f) != 0)
		goto error2;

	/* Check for binary stuff, if necessary */
	if (binbehave != BINFILE_TEXT && fileeol != '\0' &&
	    memchr(bufpos, '\0', bufrem) != NULL)
		f->binary = true;

	return (f);

error2:
	close(f->fd);
error1:
	free(f);
	return (NULL);
}