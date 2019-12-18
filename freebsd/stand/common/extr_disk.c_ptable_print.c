#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
struct ptable_entry {scalar_t__ type; int /*<<< orphan*/  index; scalar_t__ start; scalar_t__ end; } ;
struct ptable {int dummy; } ;
struct print_args {char* prefix; scalar_t__ verbose; TYPE_3__* dev; } ;
struct open_disk {int /*<<< orphan*/  sectorsize; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_unit; int /*<<< orphan*/  d_dev; } ;
struct disk_devdesc {int /*<<< orphan*/  d_partition; int /*<<< orphan*/  d_slice; TYPE_1__ dd; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_5__ {int /*<<< orphan*/  d_unit; int /*<<< orphan*/  d_dev; scalar_t__ d_opendata; } ;
struct TYPE_6__ {TYPE_2__ dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PARTNONE ; 
 scalar_t__ PART_FREEBSD ; 
 int /*<<< orphan*/  disk_close (struct disk_devdesc*) ; 
 scalar_t__ disk_open (struct disk_devdesc*,scalar_t__,int /*<<< orphan*/ ) ; 
 char* display_size (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pager_output (char*) ; 
 int /*<<< orphan*/  parttype2str (scalar_t__) ; 
 int /*<<< orphan*/  ptable_close (struct ptable*) ; 
 int ptable_iterate (struct ptable*,struct print_args*,int (*) (void*,char const*,struct ptable_entry const*)) ; 
 struct ptable* ptable_open (struct disk_devdesc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptblread ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
ptable_print(void *arg, const char *pname, const struct ptable_entry *part)
{
	struct disk_devdesc dev;
	struct print_args *pa, bsd;
	struct open_disk *od;
	struct ptable *table;
	char line[80];
	int res;
	u_int sectsize;
	uint64_t partsize;

	pa = (struct print_args *)arg;
	od = (struct open_disk *)pa->dev->dd.d_opendata;
	sectsize = od->sectorsize;
	partsize = part->end - part->start + 1;
	snprintf(line, sizeof(line), "  %s%s: %s", pa->prefix, pname,
	    parttype2str(part->type));
	if (pager_output(line))
		return (1);

	if (pa->verbose) {
		/* Emit extra tab when the line is shorter than 3 tab stops */
		if (strlen(line) < 24)
			(void) pager_output("\t");

		snprintf(line, sizeof(line), "\t%s",
		    display_size(partsize, sectsize));
		if (pager_output(line))
			return (1);
	}
	if (pager_output("\n"))
		return (1);

	res = 0;
	if (part->type == PART_FREEBSD) {
		/* Open slice with BSD label */
		dev.dd.d_dev = pa->dev->dd.d_dev;
		dev.dd.d_unit = pa->dev->dd.d_unit;
		dev.d_slice = part->index;
		dev.d_partition = D_PARTNONE;
		if (disk_open(&dev, partsize, sectsize) == 0) {
			table = ptable_open(&dev, partsize, sectsize, ptblread);
			if (table != NULL) {
				snprintf(line, sizeof(line), "  %s%s",
				    pa->prefix, pname);
				bsd.dev = pa->dev;
				bsd.prefix = line;
				bsd.verbose = pa->verbose;
				res = ptable_iterate(table, &bsd, ptable_print);
				ptable_close(table);
			}
			disk_close(&dev);
		}
	}

	return (res);
}