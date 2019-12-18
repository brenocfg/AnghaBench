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
struct bsdcat {char** argv; int argc; } ;

/* Variables and functions */
#define  OPTION_VERSION 128 
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  archive_read_free (int /*<<< orphan*/ ) ; 
 char* bsdcat_current_path ; 
 int bsdcat_getopt (struct bsdcat*) ; 
 int /*<<< orphan*/  bsdcat_next () ; 
 int /*<<< orphan*/  bsdcat_read_to_stdout (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_status ; 
 int /*<<< orphan*/  lafe_setprogname (char*,char*) ; 
 int /*<<< orphan*/  memset (struct bsdcat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  version () ; 

int
main(int argc, char **argv)
{
	struct bsdcat *bsdcat, bsdcat_storage;
	int c;

	bsdcat = &bsdcat_storage;
	memset(bsdcat, 0, sizeof(*bsdcat));

	lafe_setprogname(*argv, "bsdcat");

	bsdcat->argv = argv;
	bsdcat->argc = argc;

	while ((c = bsdcat_getopt(bsdcat)) != -1) {
		switch (c) {
		case 'h':
			usage(stdout, 0);
			break;
		case OPTION_VERSION:
			version();
			break;
		default:
			usage(stderr, 1);
		}
	}

	bsdcat_next();
	if (*bsdcat->argv == NULL) {
		bsdcat_current_path = "<stdin>";
		bsdcat_read_to_stdout(NULL);
	} else {
		while (*bsdcat->argv) {
			bsdcat_current_path = *bsdcat->argv++;
			bsdcat_read_to_stdout(bsdcat_current_path);
			bsdcat_next();
		}
		archive_read_free(a); /* Help valgrind & friends */
	}

	exit(exit_status);
}