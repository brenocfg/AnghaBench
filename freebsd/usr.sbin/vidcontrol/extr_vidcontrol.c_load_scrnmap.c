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
typedef  int /*<<< orphan*/  scrnmap ;
typedef  int /*<<< orphan*/  scrmap_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PIO_SCRNMAP ; 
 char* SCRNMAP_PATH ; 
 int decode (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * openguess (char const**,char const**,char const**,char const**,char**) ; 
 int /*<<< orphan*/  revert () ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
load_scrnmap(const char *filename)
{
	FILE *fd;
	int size;
	char *name;
	scrmap_t scrnmap;
	const char *a[] = {"", SCRNMAP_PATH, NULL};
	const char *b[] = {filename, NULL};
	const char *c[] = {"", ".scm", NULL};
	const char *d[] = {"", NULL};

	fd = openguess(a, b, c, d, &name);

	if (fd == NULL) {
		revert();
		errx(1, "screenmap file not found");
	}

	size = sizeof(scrnmap);

	if (decode(fd, (char *)&scrnmap, size) != size) {
		rewind(fd);

		if (fread(&scrnmap, 1, size, fd) != (size_t)size) {
			fclose(fd);
			revert();
			errx(1, "bad screenmap file");
		}
	}

	if (ioctl(0, PIO_SCRNMAP, &scrnmap) == -1) {
		revert();
		err(1, "loading screenmap");
	}

	fclose(fd);
}