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
struct archive_vtable {int /*<<< orphan*/  archive_write_data_block; int /*<<< orphan*/  archive_write_data; int /*<<< orphan*/  archive_write_finish_entry; int /*<<< orphan*/  archive_write_header; int /*<<< orphan*/  archive_free; int /*<<< orphan*/  archive_filter_bytes; int /*<<< orphan*/  archive_close; } ;

/* Variables and functions */
 int /*<<< orphan*/  _archive_write_disk_close ; 
 int /*<<< orphan*/  _archive_write_disk_data ; 
 int /*<<< orphan*/  _archive_write_disk_data_block ; 
 int /*<<< orphan*/  _archive_write_disk_filter_bytes ; 
 int /*<<< orphan*/  _archive_write_disk_finish_entry ; 
 int /*<<< orphan*/  _archive_write_disk_free ; 
 int /*<<< orphan*/  _archive_write_disk_header ; 

__attribute__((used)) static struct archive_vtable *
archive_write_disk_vtable(void)
{
	static struct archive_vtable av;
	static int inited = 0;

	if (!inited) {
		av.archive_close = _archive_write_disk_close;
		av.archive_filter_bytes = _archive_write_disk_filter_bytes;
		av.archive_free = _archive_write_disk_free;
		av.archive_write_header = _archive_write_disk_header;
		av.archive_write_finish_entry
		    = _archive_write_disk_finish_entry;
		av.archive_write_data = _archive_write_disk_data;
		av.archive_write_data_block = _archive_write_disk_data_block;
		inited = 1;
	}
	return (&av);
}