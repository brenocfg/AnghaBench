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
struct private_data {int compression_level; int /*<<< orphan*/ * pdata; } ;
struct archive_write_filter {char* name; int /*<<< orphan*/  code; int /*<<< orphan*/ * open; int /*<<< orphan*/ * free; int /*<<< orphan*/ * close; int /*<<< orphan*/ * options; struct private_data* data; } ;
struct archive_write {int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FILTER_BZIP2 ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct archive_write_filter* __archive_write_allocate_filter (struct archive*) ; 
 int /*<<< orphan*/ * __archive_write_program_allocate (char*) ; 
 int /*<<< orphan*/  archive_check_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_compressor_bzip2_close ; 
 int /*<<< orphan*/  archive_compressor_bzip2_free ; 
 int /*<<< orphan*/  archive_compressor_bzip2_open ; 
 int /*<<< orphan*/  archive_compressor_bzip2_options ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct private_data* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct private_data*) ; 

int
archive_write_add_filter_bzip2(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct archive_write_filter *f = __archive_write_allocate_filter(_a);
	struct private_data *data;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_add_filter_bzip2");

	data = calloc(1, sizeof(*data));
	if (data == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
		return (ARCHIVE_FATAL);
	}
	data->compression_level = 9; /* default */

	f->data = data;
	f->options = &archive_compressor_bzip2_options;
	f->close = &archive_compressor_bzip2_close;
	f->free = &archive_compressor_bzip2_free;
	f->open = &archive_compressor_bzip2_open;
	f->code = ARCHIVE_FILTER_BZIP2;
	f->name = "bzip2";
#if defined(HAVE_BZLIB_H) && defined(BZ_CONFIG_ERROR)
	return (ARCHIVE_OK);
#else
	data->pdata = __archive_write_program_allocate("bzip2");
	if (data->pdata == NULL) {
		free(data);
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
		return (ARCHIVE_FATAL);
	}
	data->compression_level = 0;
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "Using external bzip2 program");
	return (ARCHIVE_WARN);
#endif
}