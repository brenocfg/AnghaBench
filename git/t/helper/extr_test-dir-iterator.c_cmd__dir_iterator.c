#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  st_mode; } ;
struct dir_iterator {char* relative_path; char* basename; TYPE_2__ path; TYPE_1__ st; } ;

/* Variables and functions */
 unsigned int DIR_ITERATOR_FOLLOW_SYMLINKS ; 
 unsigned int DIR_ITERATOR_PEDANTIC ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int ITER_DONE ; 
 int ITER_OK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int dir_iterator_advance (struct dir_iterator*) ; 
 struct dir_iterator* dir_iterator_begin (char const*,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 char* error_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int cmd__dir_iterator(int argc, const char **argv)
{
	struct dir_iterator *diter;
	unsigned int flags = 0;
	int iter_status;

	for (++argv, --argc; *argv && starts_with(*argv, "--"); ++argv, --argc) {
		if (strcmp(*argv, "--follow-symlinks") == 0)
			flags |= DIR_ITERATOR_FOLLOW_SYMLINKS;
		else if (strcmp(*argv, "--pedantic") == 0)
			flags |= DIR_ITERATOR_PEDANTIC;
		else
			die("invalid option '%s'", *argv);
	}

	if (!*argv || argc != 1)
		die("dir-iterator needs exactly one non-option argument");

	diter = dir_iterator_begin(*argv, flags);

	if (!diter) {
		printf("dir_iterator_begin failure: %s\n", error_name(errno));
		exit(EXIT_FAILURE);
	}

	while ((iter_status = dir_iterator_advance(diter)) == ITER_OK) {
		if (S_ISDIR(diter->st.st_mode))
			printf("[d] ");
		else if (S_ISREG(diter->st.st_mode))
			printf("[f] ");
		else if (S_ISLNK(diter->st.st_mode))
			printf("[s] ");
		else
			printf("[?] ");

		printf("(%s) [%s] %s\n", diter->relative_path, diter->basename,
		       diter->path.buf);
	}

	if (iter_status != ITER_DONE) {
		printf("dir_iterator_advance failure\n");
		return 1;
	}

	return 0;
}