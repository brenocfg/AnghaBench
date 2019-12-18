#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* str_flags; void* str_shortlen; void* str_longlen; void* str_numstr; } ;
struct TYPE_6__ {char* path; scalar_t__ read_tbl; TYPE_2__ tbl; struct TYPE_6__* next; struct TYPE_6__* child; int /*<<< orphan*/  datfile; } ;
typedef  TYPE_1__ FILEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ TRUE ; 
 void* be32toh (void*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sum_tbl (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zero_tbl (TYPE_2__*) ; 

__attribute__((used)) static void
get_tbl(FILEDESC *fp)
{
	int		fd;
	FILEDESC	*child;

	if (fp->read_tbl)
		return;
	if (fp->child == NULL) {
		if ((fd = open(fp->datfile, O_RDONLY)) < 0) {
			perror(fp->datfile);
			exit(1);
		}
		if (read(fd, (char *) &fp->tbl, sizeof fp->tbl) != sizeof fp->tbl) {
			(void)fprintf(stderr,
			    "fortune: %s corrupted\n", fp->path);
			exit(1);
		}
		/* fp->tbl.str_version = be32toh(fp->tbl.str_version); */
		fp->tbl.str_numstr = be32toh(fp->tbl.str_numstr);
		fp->tbl.str_longlen = be32toh(fp->tbl.str_longlen);
		fp->tbl.str_shortlen = be32toh(fp->tbl.str_shortlen);
		fp->tbl.str_flags = be32toh(fp->tbl.str_flags);
		(void) close(fd);
	}
	else {
		zero_tbl(&fp->tbl);
		for (child = fp->child; child != NULL; child = child->next) {
			get_tbl(child);
			sum_tbl(&fp->tbl, &child->tbl);
		}
	}
	fp->read_tbl = TRUE;
}