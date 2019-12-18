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
struct TYPE_4__ {scalar_t__ expected_vol_no; } ;
struct TYPE_3__ {int volume; int solid; unsigned int vol_no; } ;
struct rar5 {TYPE_2__ vol; TYPE_1__ main; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 size_t HFL_EXTRA_DATA ; 
 size_t UINT_MAX ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int process_main_locator_extra_block (struct archive_read*,struct rar5*) ; 
 int /*<<< orphan*/  read_var_sized (struct archive_read*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_head_main(struct archive_read* a, struct rar5* rar,
    struct archive_entry* entry, size_t block_flags)
{
	(void) entry;

	int ret;
	size_t extra_data_size = 0;
	size_t extra_field_size = 0;
	size_t extra_field_id = 0;
	size_t archive_flags = 0;

	if(block_flags & HFL_EXTRA_DATA) {
		if(!read_var_sized(a, &extra_data_size, NULL))
			return ARCHIVE_EOF;
	} else {
		extra_data_size = 0;
	}

	if(!read_var_sized(a, &archive_flags, NULL)) {
		return ARCHIVE_EOF;
	}

	enum MAIN_FLAGS {
		VOLUME = 0x0001,         /* multi-volume archive */
		VOLUME_NUMBER = 0x0002,  /* volume number, first vol doesn't
					  * have it */
		SOLID = 0x0004,          /* solid archive */
		PROTECT = 0x0008,        /* contains Recovery info */
		LOCK = 0x0010,           /* readonly flag, not used */
	};

	rar->main.volume = (archive_flags & VOLUME) > 0;
	rar->main.solid = (archive_flags & SOLID) > 0;

	if(archive_flags & VOLUME_NUMBER) {
		size_t v = 0;
		if(!read_var_sized(a, &v, NULL)) {
			return ARCHIVE_EOF;
		}

		if (v > UINT_MAX) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Invalid volume number");
			return ARCHIVE_FATAL;
		}

		rar->main.vol_no = (unsigned int) v;
	} else {
		rar->main.vol_no = 0;
	}

	if(rar->vol.expected_vol_no > 0 &&
		rar->main.vol_no != rar->vol.expected_vol_no)
	{
		/* Returning EOF instead of FATAL because of strange
		 * libarchive behavior. When opening multiple files via
		 * archive_read_open_filenames(), after reading up the whole
		 * last file, the __archive_read_ahead function wraps up to
		 * the first archive instead of returning EOF. */
		return ARCHIVE_EOF;
	}

	if(extra_data_size == 0) {
		/* Early return. */
		return ARCHIVE_OK;
	}

	if(!read_var_sized(a, &extra_field_size, NULL)) {
		return ARCHIVE_EOF;
	}

	if(!read_var_sized(a, &extra_field_id, NULL)) {
		return ARCHIVE_EOF;
	}

	if(extra_field_size == 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Invalid extra field size");
		return ARCHIVE_FATAL;
	}

	enum MAIN_EXTRA {
		// Just one attribute here.
		LOCATOR = 0x01,
	};

	switch(extra_field_id) {
		case LOCATOR:
			ret = process_main_locator_extra_block(a, rar);
			if(ret != ARCHIVE_OK) {
				/* Error while parsing main locator extra
				 * block. */
				return ret;
			}

			break;
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Unsupported extra type (0x%x)",
			    (int) extra_field_id);
			return ARCHIVE_FATAL;
	}

	return ARCHIVE_OK;
}