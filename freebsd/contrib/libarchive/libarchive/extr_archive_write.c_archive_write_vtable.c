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
struct archive_vtable {int /*<<< orphan*/  archive_write_data; int /*<<< orphan*/  archive_write_finish_entry; int /*<<< orphan*/  archive_write_header; int /*<<< orphan*/  archive_free; int /*<<< orphan*/  archive_filter_count; int /*<<< orphan*/  archive_filter_name; int /*<<< orphan*/  archive_filter_code; int /*<<< orphan*/  archive_filter_bytes; int /*<<< orphan*/  archive_close; } ;

/* Variables and functions */
 int /*<<< orphan*/  _archive_filter_bytes ; 
 int /*<<< orphan*/  _archive_filter_code ; 
 int /*<<< orphan*/  _archive_filter_name ; 
 int /*<<< orphan*/  _archive_write_close ; 
 int /*<<< orphan*/  _archive_write_data ; 
 int /*<<< orphan*/  _archive_write_filter_count ; 
 int /*<<< orphan*/  _archive_write_finish_entry ; 
 int /*<<< orphan*/  _archive_write_free ; 
 int /*<<< orphan*/  _archive_write_header ; 

__attribute__((used)) static struct archive_vtable *
archive_write_vtable(void)
{
	static struct archive_vtable av;
	static int inited = 0;

	if (!inited) {
		av.archive_close = _archive_write_close;
		av.archive_filter_bytes = _archive_filter_bytes;
		av.archive_filter_code = _archive_filter_code;
		av.archive_filter_name = _archive_filter_name;
		av.archive_filter_count = _archive_write_filter_count;
		av.archive_free = _archive_write_free;
		av.archive_write_header = _archive_write_header;
		av.archive_write_finish_entry = _archive_write_finish_entry;
		av.archive_write_data = _archive_write_data;
		inited = 1;
	}
	return (&av);
}