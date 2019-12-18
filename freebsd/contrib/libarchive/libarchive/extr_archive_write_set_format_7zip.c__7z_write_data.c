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
struct archive_write {scalar_t__ format_data; } ;
struct _7zip {size_t entry_bytes_remaining; int /*<<< orphan*/  entry_crc32; int /*<<< orphan*/ * cur_file; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_Z_RUN ; 
 scalar_t__ compress_out (struct archive_write*,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,void const*,unsigned int) ; 

__attribute__((used)) static ssize_t
_7z_write_data(struct archive_write *a, const void *buff, size_t s)
{
	struct _7zip *zip;
	ssize_t bytes;

	zip = (struct _7zip *)a->format_data;

	if (s > zip->entry_bytes_remaining)
		s = (size_t)zip->entry_bytes_remaining;
	if (s == 0 || zip->cur_file == NULL)
		return (0);
	bytes = compress_out(a, buff, s, ARCHIVE_Z_RUN);
	if (bytes < 0)
		return (bytes);
	zip->entry_crc32 = crc32(zip->entry_crc32, buff, (unsigned)bytes);
	zip->entry_bytes_remaining -= bytes;
	return (bytes);
}