#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_children; int fd; char* path; char* name; char* datfile; char* posfile; int read_tbl; int was_pos_file; int /*<<< orphan*/ * inf; int /*<<< orphan*/  percent; struct TYPE_4__* parent; struct TYPE_4__* child; struct TYPE_4__* next; } ;
typedef  TYPE_1__ FILEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NO_PROB ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ WriteToDisk ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_fortfile (char*,char**,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_fp () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
all_forts(FILEDESC *fp, char *offensive)
{
	char		*sp;
	FILEDESC	*scene, *obscene;
	int		fd;
	char		*datfile, *posfile;

	if (fp->child != NULL)	/* this is a directory, not a file */
		return;
	if (!is_fortfile(offensive, &datfile, &posfile, FALSE))
		return;
	if ((fd = open(offensive, O_RDONLY)) < 0)
		return;
	DPRINTF(1, (stderr, "adding \"%s\" because of -a\n", offensive));
	scene = new_fp();
	obscene = new_fp();
	*scene = *fp;

	fp->num_children = 2;
	fp->child = scene;
	scene->next = obscene;
	obscene->next = NULL;
	scene->child = obscene->child = NULL;
	scene->parent = obscene->parent = fp;

	fp->fd = -1;
	scene->percent = obscene->percent = NO_PROB;

	obscene->fd = fd;
	obscene->inf = NULL;
	obscene->path = offensive;
	if ((sp = strrchr(offensive, '/')) == NULL)
		obscene->name = offensive;
	else
		obscene->name = ++sp;
	obscene->datfile = datfile;
	obscene->posfile = posfile;
	obscene->read_tbl = false;
	if (WriteToDisk)
		obscene->was_pos_file = (access(obscene->posfile, W_OK) >= 0);
}