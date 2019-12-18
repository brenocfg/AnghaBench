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
struct private_data {int compression_level; char block_maximum_size; int /*<<< orphan*/  block_independence; int /*<<< orphan*/  block_checksum; int /*<<< orphan*/  stream_checksum; } ;
struct archive_write_filter {int /*<<< orphan*/  archive; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_PROGRAMMER ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
archive_filter_lz4_options(struct archive_write_filter *f,
    const char *key, const char *value)
{
	struct private_data *data = (struct private_data *)f->data;

	if (strcmp(key, "compression-level") == 0) {
		int val;
		if (value == NULL || !((val = value[0] - '0') >= 1 && val <= 9) ||
		    value[1] != '\0')
			return (ARCHIVE_WARN);

#ifndef HAVE_LZ4HC_H
		if(val >= 3)
		{
			archive_set_error(f->archive, ARCHIVE_ERRNO_PROGRAMMER,
				"High compression not included in this build");
			return (ARCHIVE_FATAL);
		}
#endif
		data->compression_level = val;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "stream-checksum") == 0) {
		data->stream_checksum = value != NULL;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "block-checksum") == 0) {
		data->block_checksum = value != NULL;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "block-size") == 0) {
		if (value == NULL || !(value[0] >= '4' && value[0] <= '7') ||
		    value[1] != '\0')
			return (ARCHIVE_WARN);
		data->block_maximum_size = value[0] - '0';
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "block-dependence") == 0) {
		data->block_independence = value == NULL;
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}