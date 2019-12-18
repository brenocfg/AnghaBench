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
struct archive_write_program_data {scalar_t__ child; int /*<<< orphan*/  program_name; } ;
struct archive_write_filter {int /*<<< orphan*/  archive; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int child_write (struct archive_write_filter*,struct archive_write_program_data*,char const*,size_t) ; 

int
__archive_write_program_write(struct archive_write_filter *f,
    struct archive_write_program_data *data, const void *buff, size_t length)
{
	ssize_t ret;
	const char *buf;

	if (data->child == 0)
		return (ARCHIVE_OK);

	buf = buff;
	while (length > 0) {
		ret = child_write(f, data, buf, length);
		if (ret == -1 || ret == 0) {
			archive_set_error(f->archive, EIO,
			    "Can't write to program: %s", data->program_name);
			return (ARCHIVE_FATAL);
		}
		length -= ret;
		buf += ret;
	}
	return (ARCHIVE_OK);
}