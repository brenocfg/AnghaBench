#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_14__ {int str_numstr; } ;
struct TYPE_12__ {unsigned int str_numstr; } ;
struct TYPE_13__ {scalar_t__ percent; int pos; int /*<<< orphan*/  datfd; int /*<<< orphan*/ * child; TYPE_1__ tbl; int /*<<< orphan*/  name; struct TYPE_13__* next; } ;
typedef  TYPE_2__ FILEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* File_list ; 
 TYPE_2__* Fortfile ; 
 scalar_t__ NO_PROB ; 
 TYPE_9__ Noprob_tbl ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * Seekpts ; 
 int arc4random_uniform (int) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pos (TYPE_2__*) ; 
 int /*<<< orphan*/  get_tbl (TYPE_2__*) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_dat (TYPE_2__*) ; 
 TYPE_2__* pick_child (TYPE_2__*) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sum_noprobs (TYPE_2__*) ; 

__attribute__((used)) static void
get_fort(void)
{
	FILEDESC	*fp;
	int		choice;

	if (File_list->next == NULL || File_list->percent == NO_PROB)
		fp = File_list;
	else {
		choice = arc4random_uniform(100);
		DPRINTF(1, (stderr, "choice = %d\n", choice));
		for (fp = File_list; fp->percent != NO_PROB; fp = fp->next)
			if (choice < fp->percent)
				break;
			else {
				choice -= fp->percent;
				DPRINTF(1, (stderr,
					    "    skip \"%s\", %d%% (choice = %d)\n",
					    fp->name, fp->percent, choice));
			}
			DPRINTF(1, (stderr,
				    "using \"%s\", %d%% (choice = %d)\n",
				    fp->name, fp->percent, choice));
	}
	if (fp->percent != NO_PROB)
		get_tbl(fp);
	else {
		if (fp->next != NULL) {
			sum_noprobs(fp);
			choice = arc4random_uniform(Noprob_tbl.str_numstr);
			DPRINTF(1, (stderr, "choice = %d (of %u) \n", choice,
				    Noprob_tbl.str_numstr));
			while ((unsigned int)choice >= fp->tbl.str_numstr) {
				choice -= fp->tbl.str_numstr;
				fp = fp->next;
				DPRINTF(1, (stderr,
					    "    skip \"%s\", %u (choice = %d)\n",
					    fp->name, fp->tbl.str_numstr,
					    choice));
			}
			DPRINTF(1, (stderr, "using \"%s\", %u\n", fp->name,
				    fp->tbl.str_numstr));
		}
		get_tbl(fp);
	}
	if (fp->child != NULL) {
		DPRINTF(1, (stderr, "picking child\n"));
		fp = pick_child(fp);
	}
	Fortfile = fp;
	get_pos(fp);
	open_dat(fp);
	lseek(fp->datfd,
	    (off_t) (sizeof fp->tbl + fp->pos * sizeof Seekpts[0]), SEEK_SET);
	read(fp->datfd, Seekpts, sizeof Seekpts);
	Seekpts[0] = be64toh(Seekpts[0]);
	Seekpts[1] = be64toh(Seekpts[1]);
}