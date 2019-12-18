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
struct print_args {char* prefix; int verbose; struct disk_devdesc* dev; } ;
struct open_disk {int /*<<< orphan*/  table; } ;
struct TYPE_2__ {scalar_t__ d_opendata; } ;
struct disk_devdesc {TYPE_1__ dd; } ;

/* Variables and functions */
 int ptable_iterate (int /*<<< orphan*/ ,struct print_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptable_print ; 

int
disk_print(struct disk_devdesc *dev, char *prefix, int verbose)
{
	struct open_disk *od;
	struct print_args pa;

	/* Disk should be opened */
	od = (struct open_disk *)dev->dd.d_opendata;
	pa.dev = dev;
	pa.prefix = prefix;
	pa.verbose = verbose;
	return (ptable_iterate(od->table, &pa, ptable_print));
}