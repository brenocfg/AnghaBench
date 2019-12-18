#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct archive_write {size_t null_length; int /*<<< orphan*/  nulls; scalar_t__ format_data; } ;
struct TYPE_3__ {scalar_t__ total_out; scalar_t__ total_in; } ;
struct _7zip {scalar_t__ entry_bytes_remaining; TYPE_2__* cur_file; int /*<<< orphan*/  entry_crc32; TYPE_1__ stream; int /*<<< orphan*/  total_bytes_uncompressed; int /*<<< orphan*/  total_bytes_compressed; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  crc32; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 scalar_t__ _7z_write_data (struct archive_write*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
_7z_finish_entry(struct archive_write *a)
{
	struct _7zip *zip;
	size_t s;
	ssize_t r;

	zip = (struct _7zip *)a->format_data;
	if (zip->cur_file == NULL)
		return (ARCHIVE_OK);

	while (zip->entry_bytes_remaining > 0) {
		s = (size_t)zip->entry_bytes_remaining;
		if (s > a->null_length)
			s = a->null_length;
		r = _7z_write_data(a, a->nulls, s);
		if (r < 0)
			return ((int)r);
	}
	zip->total_bytes_compressed += zip->stream.total_in;
	zip->total_bytes_uncompressed += zip->stream.total_out;
	zip->cur_file->crc32 = zip->entry_crc32;
	zip->cur_file = NULL;

	return (ARCHIVE_OK);
}