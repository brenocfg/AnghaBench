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
typedef  scalar_t__ uint32_t ;
typedef  int time_t ;
struct stat {scalar_t__ st_mtime; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ fflag ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int gz_compress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,char*,scalar_t__) ; 
 int /*<<< orphan*/  infile_set (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_warn (char*) ; 
 int /*<<< orphan*/  maybe_warnx (char*) ; 
 int /*<<< orphan*/  print_verbage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tflag ; 
 int time (int /*<<< orphan*/ *) ; 
 scalar_t__ vflag ; 

__attribute__((used)) static void
handle_stdout(void)
{
	off_t gsize;
#ifndef SMALL
	off_t usize;
	struct stat sb;
	time_t systime;
	uint32_t mtime;
	int ret;

	infile_set("(stdout)", 0);

	if (fflag == 0 && isatty(STDOUT_FILENO)) {
		maybe_warnx("standard output is a terminal -- ignoring");
		return;
	}

	/* If stdin is a file use its mtime, otherwise use current time */
	ret = fstat(STDIN_FILENO, &sb);
	if (ret < 0) {
		maybe_warn("Can't stat stdin");
		return;
	}

	if (S_ISREG(sb.st_mode)) {
		infile_set("(stdout)", sb.st_size);
		mtime = (uint32_t)sb.st_mtime;
	} else {
		systime = time(NULL);
		if (systime == -1) {
			maybe_warn("time");
			return;
		}
		mtime = (uint32_t)systime;
	}
	 		
	usize =
#endif
		gz_compress(STDIN_FILENO, STDOUT_FILENO, &gsize, "", mtime);
#ifndef SMALL
        if (vflag && !tflag && usize != -1 && gsize != -1)
		print_verbage(NULL, NULL, usize, gsize);
#endif
}