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
typedef  int uint8_t ;
struct file {unsigned int flg; TYPE_2__* times; struct file* next; } ;
struct archive_write {scalar_t__ format_data; } ;
struct TYPE_3__ {struct file* first; } ;
struct _7zip {int* total_number_time_defined; int total_number_entry; TYPE_1__ file_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  time_ns; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_Z_RUN ; 
 int /*<<< orphan*/  archive_le64enc (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ compress_out (struct archive_write*,int*,int,int /*<<< orphan*/ ) ; 
 int enc_uint64 (struct archive_write*,int) ; 
 int /*<<< orphan*/  utcToFiletime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_time(struct archive_write *a, uint8_t type, unsigned flg, int ti)
{
	uint8_t filetime[8];
	struct _7zip *zip = (struct _7zip *)a->format_data;
	struct file *file;
	int r;
	uint8_t b, mask;

	/*
	 * Make Time Bools.
	 */
	if (zip->total_number_time_defined[ti] == zip->total_number_entry) {
		/* Write Time Type. */
		r = enc_uint64(a, type);
		if (r < 0)
			return (r);
		/* Write EmptyStream Size. */
		r = enc_uint64(a, 2 + zip->total_number_entry * 8);
		if (r < 0)
			return (r);
		/* All are defined. */
		r = enc_uint64(a, 1);
		if (r < 0)
			return (r);
	} else {
		if (zip->total_number_time_defined[ti] == 0)
			return (ARCHIVE_OK);

		/* Write Time Type. */
		r = enc_uint64(a, type);
		if (r < 0)
			return (r);
		/* Write EmptyStream Size. */
		r = enc_uint64(a, 2 + ((zip->total_number_entry + 7) >> 3)
			+ zip->total_number_time_defined[ti] * 8);
		if (r < 0)
			return (r);

		/* All are not defined. */
		r = enc_uint64(a, 0);
		if (r < 0)
			return (r);

		b = 0;
		mask = 0x80;
		file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->flg & flg)
				b |= mask;
			mask >>= 1;
			if (mask == 0) {
				r = (int)compress_out(a, &b, 1, ARCHIVE_Z_RUN);
				if (r < 0)
					return (r);
				mask = 0x80;
				b = 0;
			}
		}
		if (mask != 0x80) {
			r = (int)compress_out(a, &b, 1, ARCHIVE_Z_RUN);
			if (r < 0)
				return (r);
		}
	}

	/* External. */
	r = enc_uint64(a, 0);
	if (r < 0)
		return (r);


	/*
	 * Make Times.
	 */
	file = zip->file_list.first;
	for (;file != NULL; file = file->next) {
		if ((file->flg & flg) == 0)
			continue;
		archive_le64enc(filetime, utcToFiletime(file->times[ti].time,
			file->times[ti].time_ns));
		r = (int)compress_out(a, filetime, 8, ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}

	return (ARCHIVE_OK);
}