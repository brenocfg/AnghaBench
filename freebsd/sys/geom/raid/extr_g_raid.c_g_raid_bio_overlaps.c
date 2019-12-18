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
struct bio {scalar_t__ bio_offset; scalar_t__ bio_length; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */

__attribute__((used)) static int
g_raid_bio_overlaps(const struct bio *bp, off_t lstart, off_t len)
{
	/*
	 * 5 cases:
	 * (1) bp entirely below NO
	 * (2) bp entirely above NO
	 * (3) bp start below, but end in range YES
	 * (4) bp entirely within YES
	 * (5) bp starts within, ends above YES
	 *
	 * lock range 10-19 (offset 10 length 10)
	 * (1) 1-5: first if kicks it out
	 * (2) 30-35: second if kicks it out
	 * (3) 5-15: passes both ifs
	 * (4) 12-14: passes both ifs
	 * (5) 19-20: passes both
	 */
	off_t lend = lstart + len - 1;
	off_t bstart = bp->bio_offset;
	off_t bend = bp->bio_offset + bp->bio_length - 1;

	if (bend < lstart)
		return (0);
	if (lend < bstart)
		return (0);
	return (1);
}