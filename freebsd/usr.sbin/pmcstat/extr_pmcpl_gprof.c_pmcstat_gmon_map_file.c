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
struct pmcstat_gmonfile {int /*<<< orphan*/  pgf_gmondata; int /*<<< orphan*/  pgf_ndatabytes; int /*<<< orphan*/  pgf_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int MAP_NOSYNC ; 
 int MAP_SHARED ; 
 int O_NOFOLLOW ; 
 int O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 char* pmcstat_string_unintern (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmcstat_gmon_map_file(struct pmcstat_gmonfile *pgf)
{
	int fd;
	const char *pathname;

	pathname = pmcstat_string_unintern(pgf->pgf_name);

	/* the gmon.out file must already exist */
	if ((fd = open(pathname, O_RDWR | O_NOFOLLOW, 0)) < 0)
		err(EX_OSERR, "ERROR: cannot open \"%s\"", pathname);

	pgf->pgf_gmondata = mmap(NULL, pgf->pgf_ndatabytes,
	    PROT_READ|PROT_WRITE, MAP_NOSYNC|MAP_SHARED, fd, 0);

	if (pgf->pgf_gmondata == MAP_FAILED)
		err(EX_OSERR, "ERROR: cannot map \"%s\"", pathname);

	(void) close(fd);
}