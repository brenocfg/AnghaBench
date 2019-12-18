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
struct file {TYPE_1__* f_mapping; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t get_size(loff_t offset, loff_t sizelimit, struct file *file)
{
	loff_t loopsize;

	/* Compute loopsize in bytes */
	loopsize = i_size_read(file->f_mapping->host);
	if (offset > 0)
		loopsize -= offset;
	/* offset is beyond i_size, weird but possible */
	if (loopsize < 0)
		return 0;

	if (sizelimit > 0 && sizelimit < loopsize)
		loopsize = sizelimit;
	/*
	 * Unfortunately, if we want to do I/O on the device,
	 * the number of 512-byte sectors has to fit into a sector_t.
	 */
	return loopsize >> 9;
}