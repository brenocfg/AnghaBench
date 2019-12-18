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
struct private_data {scalar_t__ compression_level; scalar_t__ block_maximum_size; scalar_t__ stream_checksum; scalar_t__ block_independence; int /*<<< orphan*/  pdata; scalar_t__ block_checksum; } ;
struct archive_write_filter {int /*<<< orphan*/  write; scalar_t__ data; } ;
struct archive_string {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int __archive_write_program_open (struct archive_write_filter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_filter_lz4_write ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,scalar_t__) ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_strcpy (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 

__attribute__((used)) static int
archive_filter_lz4_open(struct archive_write_filter *f)
{
	struct private_data *data = (struct private_data *)f->data;
	struct archive_string as;
	int r;

	archive_string_init(&as);
	archive_strcpy(&as, "lz4 -z -q -q");

	/* Specify a compression level. */
	if (data->compression_level > 0) {
		archive_strcat(&as, " -");
		archive_strappend_char(&as, '0' + data->compression_level);
	}
	/* Specify a block size. */
	archive_strcat(&as, " -B");
	archive_strappend_char(&as, '0' + data->block_maximum_size);

	if (data->block_checksum)
		archive_strcat(&as, " -BX");
	if (data->stream_checksum == 0)
		archive_strcat(&as, " --no-frame-crc");
	if (data->block_independence == 0)
		archive_strcat(&as, " -BD");

	f->write = archive_filter_lz4_write;

	r = __archive_write_program_open(f, data->pdata, as.s);
	archive_string_free(&as);
	return (r);
}