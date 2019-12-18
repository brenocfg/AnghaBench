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
typedef  scalar_t__ uint64_t ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MADV_SEQUENTIAL ; 
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ask (char*,char const*) ; 
 scalar_t__ batch ; 
 char* buf ; 
 scalar_t__ check_only ; 
 int /*<<< orphan*/  close (int) ; 
 int creat (char const*,int) ; 
 int debug ; 
 char* empty_line ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  filemode ; 
 scalar_t__ force ; 
 int /*<<< orphan*/  free (char**) ; 
 char** i_ptr ; 
 size_t i_size ; 
 char* i_womp ; 
 size_t input_lines ; 
 int last_line_missing_eol ; 
 int /*<<< orphan*/  madvise (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makedirs (char const*,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,size_t) ; 
 scalar_t__ ok_to_create_file ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int out_of_mem ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pfatal (char*,char const*) ; 
 int /*<<< orphan*/  reallocate_lines (size_t*) ; 
 int /*<<< orphan*/  rev_in_string (char*) ; 
 char const* revision ; 
 int /*<<< orphan*/  say (char*,...) ; 
 int /*<<< orphan*/  set_hunkmax () ; 
 int stat (char const*,struct stat*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static bool
plan_a(const char *filename)
{
	int		ifd, statfailed;
	char		*p, *s;
	struct stat	filestat;
	ptrdiff_t	sz;
	size_t		i;
	size_t		iline, lines_allocated;

#ifdef DEBUGGING
	if (debug & 8)
		return false;
#endif

	if (filename == NULL || *filename == '\0')
		return false;

	statfailed = stat(filename, &filestat);
	if (statfailed && ok_to_create_file) {
		if (verbose)
			say("(Creating file %s...)\n", filename);

		/*
		 * in check_patch case, we still display `Creating file' even
		 * though we're not. The rule is that -C should be as similar
		 * to normal patch behavior as possible
		 */
		if (check_only)
			return true;
		makedirs(filename, true);
		close(creat(filename, 0666));
		statfailed = stat(filename, &filestat);
	}
	if (statfailed)
		fatal("can't find %s\n", filename);
	filemode = filestat.st_mode;
	if (!S_ISREG(filemode))
		fatal("%s is not a normal file--can't patch\n", filename);
	if ((uint64_t)filestat.st_size > SIZE_MAX) {
		say("block too large to mmap\n");
		return false;
	}
	i_size = (size_t)filestat.st_size;
	if (out_of_mem) {
		set_hunkmax();	/* make sure dynamic arrays are allocated */
		out_of_mem = false;
		return false;	/* force plan b because plan a bombed */
	}
	if ((ifd = open(filename, O_RDONLY)) < 0)
		pfatal("can't open file %s", filename);

	if (i_size) {
		i_womp = mmap(NULL, i_size, PROT_READ, MAP_PRIVATE, ifd, 0);
		if (i_womp == MAP_FAILED) {
			perror("mmap failed");
			i_womp = NULL;
			close(ifd);
			return false;
		}
	} else {
		i_womp = NULL;
	}

	close(ifd);
	if (i_size)
		madvise(i_womp, i_size, MADV_SEQUENTIAL);

	/* estimate the number of lines */
	lines_allocated = i_size / 25;
	if (lines_allocated < 100)
		lines_allocated = 100;

	if (!reallocate_lines(&lines_allocated))
		return false;

	/* now scan the buffer and build pointer array */
	iline = 1;
	i_ptr[iline] = i_womp;
	/*
	 * Testing for NUL here actively breaks files that innocently use NUL
	 * for other reasons. mmap(2) succeeded, just scan the whole buffer.
	 */
	for (s = i_womp, i = 0; i < i_size; s++, i++) {
		if (*s == '\n') {
			if (iline == lines_allocated) {
				if (!reallocate_lines(&lines_allocated))
					return false;
			}
			/* these are NOT NUL terminated */
			i_ptr[++iline] = s + 1;
		}
	}
	/* if the last line contains no EOL, append one */
	if (i_size > 0 && i_womp[i_size - 1] != '\n') {
		last_line_missing_eol = true;
		/* fix last line */
		sz = s - i_ptr[iline];
		p = malloc(sz + 1);
		if (p == NULL) {
			free(i_ptr);
			i_ptr = NULL;
			munmap(i_womp, i_size);
			i_womp = NULL;
			return false;
		}

		memcpy(p, i_ptr[iline], sz);
		p[sz] = '\n';
		i_ptr[iline] = p;
		/* count the extra line and make it point to some valid mem */
		i_ptr[++iline] = empty_line;
	} else
		last_line_missing_eol = false;

	input_lines = iline - 1;

	/* now check for revision, if any */

	if (revision != NULL) {
		if (i_womp == NULL || !rev_in_string(i_womp)) {
			if (force) {
				if (verbose)
					say("Warning: this file doesn't appear "
					    "to be the %s version--patching anyway.\n",
					    revision);
			} else if (batch) {
				fatal("this file doesn't appear to be the "
				    "%s version--aborting.\n",
				    revision);
			} else {
				ask("This file doesn't appear to be the "
				    "%s version--patch anyway? [n] ",
				    revision);
				if (*buf != 'y')
					fatal("aborted\n");
			}
		} else if (verbose)
			say("Good.  This file appears to be the %s version.\n",
			    revision);
	}
	return true;		/* plan a will work */
}