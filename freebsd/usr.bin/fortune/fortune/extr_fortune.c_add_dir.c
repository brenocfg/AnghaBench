#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dirent {scalar_t__ d_namlen; int /*<<< orphan*/  d_name; } ;
struct TYPE_5__ {int fd; char* path; scalar_t__ num_children; int /*<<< orphan*/  child; } ;
typedef  TYPE_1__ FILEDESC ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  NO_PROB ; 
 int TRUE ; 
 scalar_t__ add_file (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/  close (int) ; 
 char* copy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
add_dir(FILEDESC *fp)
{
	DIR		*dir;
	struct dirent	*dirent;
	FILEDESC	*tailp;
	char		*name;

	(void) close(fp->fd);
	fp->fd = -1;
	if ((dir = opendir(fp->path)) == NULL) {
		perror(fp->path);
		return (FALSE);
	}
	tailp = NULL;
	DPRINTF(1, (stderr, "adding dir \"%s\"\n", fp->path));
	fp->num_children = 0;
	while ((dirent = readdir(dir)) != NULL) {
		if (dirent->d_namlen == 0)
			continue;
		name = copy(dirent->d_name, dirent->d_namlen);
		if (add_file(NO_PROB, name, fp->path, &fp->child, &tailp, fp))
			fp->num_children++;
		else
			free(name);
	}
	if (fp->num_children == 0) {
		(void) fprintf(stderr,
		    "fortune: %s: No fortune files in directory.\n", fp->path);
		return (FALSE);
	}

	return (TRUE);
}