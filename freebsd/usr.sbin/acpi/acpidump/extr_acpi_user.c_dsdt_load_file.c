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
typedef  int /*<<< orphan*/  uint8_t ;
struct stat {int /*<<< orphan*/  st_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ acpi_checksum (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int acpi_mem_fd ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  maplist ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

ACPI_TABLE_HEADER *
dsdt_load_file(char *infile)
{
	ACPI_TABLE_HEADER *sdt;
	uint8_t		*dp;
	struct stat	 sb;

	if ((acpi_mem_fd = open(infile, O_RDONLY)) == -1)
		errx(1, "opening %s", infile);

	LIST_INIT(&maplist);

	if (fstat(acpi_mem_fd, &sb) == -1)
		errx(1, "fstat %s", infile);

	dp = mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, acpi_mem_fd, 0);
	if (dp == NULL)
		errx(1, "mmap %s", infile);

	sdt = (ACPI_TABLE_HEADER *)dp;
	if (strncmp(dp, ACPI_SIG_DSDT, 4) != 0 ||
	    acpi_checksum(sdt, sdt->Length) != 0)
		return (NULL);

	return (sdt);
}