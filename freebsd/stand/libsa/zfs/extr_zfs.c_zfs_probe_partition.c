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
struct zfs_probe_args {char* devname; int fd; int /*<<< orphan*/  secsz; int /*<<< orphan*/  pool_guid; } ;
struct ptable_entry {scalar_t__ type; scalar_t__ start; scalar_t__ end; } ;
struct ptable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ PART_FREEBSD ; 
 scalar_t__ PART_FREEBSD_ZFS ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptable_close (struct ptable*) ; 
 int /*<<< orphan*/  ptable_iterate (struct ptable*,struct zfs_probe_args*,int (*) (void*,char const*,struct ptable_entry const*)) ; 
 struct ptable* ptable_open (struct zfs_probe_args*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_diskread ; 
 int zfs_probe (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_probe_partition(void *arg, const char *partname,
    const struct ptable_entry *part)
{
	struct zfs_probe_args *ppa, pa;
	struct ptable *table;
	char devname[32];
	int ret;

	/* Probe only freebsd-zfs and freebsd partitions */
	if (part->type != PART_FREEBSD &&
	    part->type != PART_FREEBSD_ZFS)
		return (0);

	ppa = (struct zfs_probe_args *)arg;
	strncpy(devname, ppa->devname, strlen(ppa->devname) - 1);
	devname[strlen(ppa->devname) - 1] = '\0';
	sprintf(devname, "%s%s:", devname, partname);
	pa.fd = open(devname, O_RDONLY);
	if (pa.fd == -1)
		return (0);
	ret = zfs_probe(pa.fd, ppa->pool_guid);
	if (ret == 0)
		return (0);
	/* Do we have BSD label here? */
	if (part->type == PART_FREEBSD) {
		pa.devname = devname;
		pa.pool_guid = ppa->pool_guid;
		pa.secsz = ppa->secsz;
		table = ptable_open(&pa, part->end - part->start + 1,
		    ppa->secsz, zfs_diskread);
		if (table != NULL) {
			ptable_iterate(table, &pa, zfs_probe_partition);
			ptable_close(table);
		}
	}
	close(pa.fd);
	return (0);
}