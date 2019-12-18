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
struct disklabel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_fd; } ;

/* Variables and functions */
 scalar_t__ BBSIZE ; 
 int /*<<< orphan*/  MAXPARTITIONS ; 
 scalar_t__ bootarea ; 
 scalar_t__ bsd_disklabel_le_dec (scalar_t__,struct disklabel*,int /*<<< orphan*/ ) ; 
 TYPE_1__ disk ; 
 scalar_t__ disktype ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct disklabel* getdiskbyname (scalar_t__) ; 
 scalar_t__ is_file ; 
 scalar_t__ read (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int sectorsize ; 

struct disklabel *
getdisklabel(void)
{
	static struct disklabel lab;
	struct disklabel *lp;

	if (is_file) {
		if (read(disk.d_fd, bootarea, BBSIZE) != BBSIZE)
			err(4, "cannot read bootarea");
		if (bsd_disklabel_le_dec(
		    bootarea + (0 /* labeloffset */ +
				1 /* labelsoffset */ * sectorsize),
		    &lab, MAXPARTITIONS))
			errx(1, "no valid label found");

		lp = &lab;
		return &lab;
	}

	if (disktype) {
		lp = getdiskbyname(disktype);
		if (lp != NULL)
			return (lp);
	}
	return (NULL);
}