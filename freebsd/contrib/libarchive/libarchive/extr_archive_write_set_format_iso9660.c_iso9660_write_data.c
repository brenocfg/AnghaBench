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
struct iso9660 {size_t bytes_remaining; TYPE_1__* cur_file; } ;
struct archive_write {struct iso9660* format_data; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 scalar_t__ AE_IFREG ; 
 scalar_t__ archive_entry_filetype (int /*<<< orphan*/ ) ; 
 scalar_t__ write_iso9660_data (struct archive_write*,void const*,size_t) ; 

__attribute__((used)) static ssize_t
iso9660_write_data(struct archive_write *a, const void *buff, size_t s)
{
	struct iso9660 *iso9660 = a->format_data;
	ssize_t r;

	if (iso9660->cur_file == NULL)
		return (0);
	if (archive_entry_filetype(iso9660->cur_file->entry) != AE_IFREG)
		return (0);
	if (s > iso9660->bytes_remaining)
		s = (size_t)iso9660->bytes_remaining;
	if (s == 0)
		return (0);

	r = write_iso9660_data(a, buff, s);
	if (r > 0)
		iso9660->bytes_remaining -= r;
	return (r);
}