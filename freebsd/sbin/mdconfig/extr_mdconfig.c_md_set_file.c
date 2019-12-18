#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {scalar_t__ md_mediasize; int /*<<< orphan*/  md_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int fstat (int,struct stat*) ; 
 TYPE_1__ mdio ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realpath (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
md_set_file(const char *fn)
{
	struct stat sb;
	int fd;

	if (realpath(fn, mdio.md_file) == NULL)
		err(1, "could not find full path for %s", fn);
	fd = open(mdio.md_file, O_RDONLY);
	if (fd < 0)
		err(1, "could not open %s", fn);
	if (fstat(fd, &sb) == -1)
		err(1, "could not stat %s", fn);
	if (!S_ISREG(sb.st_mode))
		errx(1, "%s is not a regular file", fn);
	if (mdio.md_mediasize == 0)
		mdio.md_mediasize = sb.st_size;
	close(fd);
}