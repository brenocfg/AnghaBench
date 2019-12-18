#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  was_pos_file; int /*<<< orphan*/  pos; int /*<<< orphan*/  posfile; } ;

/* Variables and functions */
 int CPERS ; 
 int Fort_len ; 
 TYPE_1__* Fortfile ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LOCK_EX ; 
 int /*<<< orphan*/  LOCK_UN ; 
 scalar_t__ Long_only ; 
 int /*<<< orphan*/  MINW ; 
 scalar_t__ Match ; 
 scalar_t__ SLEN ; 
 scalar_t__ Short_only ; 
 scalar_t__ Wait ; 
 int WriteToDisk ; 
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int) ; 
 int creat (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  display (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ find_matches () ; 
 int /*<<< orphan*/  flock (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fortlen () ; 
 int /*<<< orphan*/  get_fort () ; 
 int /*<<< orphan*/  getargs (int,char**) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  getpath () ; 
 int /*<<< orphan*/  init_prob () ; 
 scalar_t__ max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (unsigned int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

int
main(int argc, char *argv[])
{
	int	fd;

	if (getenv("FORTUNE_SAVESTATE") != NULL)
		WriteToDisk = true;

	(void) setlocale(LC_ALL, "");

	getpath();
	getargs(argc, argv);

	if (Match)
		exit(find_matches() != 0);

	init_prob();
	do {
		get_fort();
	} while ((Short_only && fortlen() > SLEN) ||
		 (Long_only && fortlen() <= SLEN));

	display(Fortfile);

	if (WriteToDisk) {
		if ((fd = creat(Fortfile->posfile, 0666)) < 0) {
			perror(Fortfile->posfile);
			exit(1);
		}
		/*
		 * if we can, we exclusive lock, but since it isn't very
		 * important, we just punt if we don't have easy locking
		 * available.
		 */
		flock(fd, LOCK_EX);
		write(fd, (char *) &Fortfile->pos, sizeof Fortfile->pos);
		if (!Fortfile->was_pos_file)
		chmod(Fortfile->path, 0666);
		flock(fd, LOCK_UN);
	}
	if (Wait) {
		if (Fort_len == 0)
			(void) fortlen();
		sleep((unsigned int) max(Fort_len / CPERS, MINW));
	}

	exit(0);
}