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
struct archive_vtable {int /*<<< orphan*/  archive_read_next_header2; int /*<<< orphan*/  archive_read_next_header; int /*<<< orphan*/  archive_read_data_block; int /*<<< orphan*/  archive_close; int /*<<< orphan*/  archive_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  _archive_read_close ; 
 int /*<<< orphan*/  _archive_read_data_block ; 
 int /*<<< orphan*/  _archive_read_free ; 
 int /*<<< orphan*/  _archive_read_next_header ; 
 int /*<<< orphan*/  _archive_read_next_header2 ; 

__attribute__((used)) static struct archive_vtable *
archive_read_disk_vtable(void)
{
	static struct archive_vtable av;
	static int inited = 0;

	if (!inited) {
		av.archive_free = _archive_read_free;
		av.archive_close = _archive_read_close;
		av.archive_read_data_block = _archive_read_data_block;
		av.archive_read_next_header = _archive_read_next_header;
		av.archive_read_next_header2 = _archive_read_next_header2;
		inited = 1;
	}
	return (&av);
}