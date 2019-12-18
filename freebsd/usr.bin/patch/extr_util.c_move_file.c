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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EXDEV ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ backup_file (char const*) ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  buf_size ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ copy_file (char const*,char const*) ; 
 int debug ; 
 scalar_t__ errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfatal (char*,...) ; 
 scalar_t__ read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rename (char const*,char const*) ; 
 int /*<<< orphan*/  say (char*,char const*,...) ; 
 scalar_t__ strEQ (char const*,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
move_file(const char *from, const char *to)
{
	int	fromfd;
	ssize_t	i;

	/* to stdout? */

	if (strEQ(to, "-")) {
#ifdef DEBUGGING
		if (debug & 4)
			say("Moving %s to stdout.\n", from);
#endif
		fromfd = open(from, O_RDONLY);
		if (fromfd < 0)
			pfatal("internal error, can't reopen %s", from);
		while ((i = read(fromfd, buf, buf_size)) > 0)
			if (write(STDOUT_FILENO, buf, i) != i)
				pfatal("write failed");
		close(fromfd);
		return 0;
	}
	if (backup_file(to) < 0) {
		say("Can't backup %s, output is in %s: %s\n", to, from,
		    strerror(errno));
		return -1;
	}
#ifdef DEBUGGING
	if (debug & 4)
		say("Moving %s to %s.\n", from, to);
#endif
	if (rename(from, to) < 0) {
		if (errno != EXDEV || copy_file(from, to) < 0) {
			say("Can't create %s, output is in %s: %s\n",
			    to, from, strerror(errno));
			return -1;
		}
	}
	return 0;
}