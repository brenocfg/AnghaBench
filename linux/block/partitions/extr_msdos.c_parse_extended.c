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
typedef  int /*<<< orphan*/  u32 ;
struct partition {int dummy; } ;
struct parsed_partitions {size_t next; size_t limit; TYPE_1__* parts; int /*<<< orphan*/  bdev; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int /*<<< orphan*/  ADDPART_FLAG_RAID ; 
 scalar_t__ LINUX_RAID_PARTITION ; 
 scalar_t__ SYS_IND (struct partition*) ; 
 int bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 scalar_t__ is_extended_partition (struct partition*) ; 
 int /*<<< orphan*/  msdos_magic_present (unsigned char*) ; 
 scalar_t__ nr_sects (struct partition*) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,size_t,scalar_t__,scalar_t__) ; 
 unsigned char* read_part_sector (struct parsed_partitions*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_info (struct parsed_partitions*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ start_sect (struct partition*) ; 

__attribute__((used)) static void parse_extended(struct parsed_partitions *state,
			   sector_t first_sector, sector_t first_size,
			   u32 disksig)
{
	struct partition *p;
	Sector sect;
	unsigned char *data;
	sector_t this_sector, this_size;
	sector_t sector_size = bdev_logical_block_size(state->bdev) / 512;
	int loopct = 0;		/* number of links followed
				   without finding a data partition */
	int i;

	this_sector = first_sector;
	this_size = first_size;

	while (1) {
		if (++loopct > 100)
			return;
		if (state->next == state->limit)
			return;
		data = read_part_sector(state, this_sector, &sect);
		if (!data)
			return;

		if (!msdos_magic_present(data + 510))
			goto done;

		p = (struct partition *) (data + 0x1be);

		/*
		 * Usually, the first entry is the real data partition,
		 * the 2nd entry is the next extended partition, or empty,
		 * and the 3rd and 4th entries are unused.
		 * However, DRDOS sometimes has the extended partition as
		 * the first entry (when the data partition is empty),
		 * and OS/2 seems to use all four entries.
		 */

		/*
		 * First process the data partition(s)
		 */
		for (i = 0; i < 4; i++, p++) {
			sector_t offs, size, next;

			if (!nr_sects(p) || is_extended_partition(p))
				continue;

			/* Check the 3rd and 4th entries -
			   these sometimes contain random garbage */
			offs = start_sect(p)*sector_size;
			size = nr_sects(p)*sector_size;
			next = this_sector + offs;
			if (i >= 2) {
				if (offs + size > this_size)
					continue;
				if (next < first_sector)
					continue;
				if (next + size > first_sector + first_size)
					continue;
			}

			put_partition(state, state->next, next, size);
			set_info(state, state->next, disksig);
			if (SYS_IND(p) == LINUX_RAID_PARTITION)
				state->parts[state->next].flags = ADDPART_FLAG_RAID;
			loopct = 0;
			if (++state->next == state->limit)
				goto done;
		}
		/*
		 * Next, process the (first) extended partition, if present.
		 * (So far, there seems to be no reason to make
		 *  parse_extended()  recursive and allow a tree
		 *  of extended partitions.)
		 * It should be a link to the next logical partition.
		 */
		p -= 4;
		for (i = 0; i < 4; i++, p++)
			if (nr_sects(p) && is_extended_partition(p))
				break;
		if (i == 4)
			goto done;	 /* nothing left to do */

		this_sector = first_sector + start_sect(p) * sector_size;
		this_size = nr_sects(p) * sector_size;
		put_dev_sector(sect);
	}
done:
	put_dev_sector(sect);
}