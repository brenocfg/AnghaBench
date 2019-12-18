#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int switch_multivolume; size_t last_unstore_ptr; } ;
struct TYPE_7__ {scalar_t__ bytes_remaining; } ;
struct TYPE_6__ {scalar_t__ split_after; } ;
struct TYPE_5__ {scalar_t__ volume; } ;
struct rar5 {TYPE_4__ cstate; TYPE_3__ file; TYPE_2__ generic; TYPE_1__ main; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  size_t int64_t ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int advance_multivolume (struct archive_read*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int consume (struct archive_read*,size_t) ; 
 size_t rar5_min (scalar_t__,int) ; 
 int /*<<< orphan*/  read_ahead (struct archive_read*,size_t,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  update_crc (struct rar5*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int do_unstore_file(struct archive_read* a,
    struct rar5* rar, const void** buf, size_t* size, int64_t* offset)
{
	const uint8_t* p;

	if(rar->file.bytes_remaining == 0 && rar->main.volume > 0 &&
	    rar->generic.split_after > 0)
	{
		int ret;

		rar->cstate.switch_multivolume = 1;
		ret = advance_multivolume(a);
		rar->cstate.switch_multivolume = 0;

		if(ret != ARCHIVE_OK) {
			/* Failed to advance to next multivolume archive
			 * file. */
			return ret;
		}
	}

	size_t to_read = rar5_min(rar->file.bytes_remaining, 64 * 1024);
	if(to_read == 0) {
		return ARCHIVE_EOF;
	}

	if(!read_ahead(a, to_read, &p)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "I/O error when unstoring file");
		return ARCHIVE_FATAL;
	}

	if(ARCHIVE_OK != consume(a, to_read)) {
		return ARCHIVE_EOF;
	}

	if(buf)    *buf = p;
	if(size)   *size = to_read;
	if(offset) *offset = rar->cstate.last_unstore_ptr;

	rar->file.bytes_remaining -= to_read;
	rar->cstate.last_unstore_ptr += to_read;

	update_crc(rar, p, to_read);
	return ARCHIVE_OK;
}