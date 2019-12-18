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
struct TYPE_4__ {int method; } ;
struct TYPE_3__ {scalar_t__ service; } ;
struct rar5 {TYPE_2__ cstate; TYPE_1__ file; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int do_unstore_file (struct archive_read*,struct rar5*,void const**,size_t*,int /*<<< orphan*/ *) ; 
 int uncompress_file (struct archive_read*) ; 

__attribute__((used)) static int do_unpack(struct archive_read* a, struct rar5* rar,
    const void** buf, size_t* size, int64_t* offset)
{
	enum COMPRESSION_METHOD {
		STORE = 0, FASTEST = 1, FAST = 2, NORMAL = 3, GOOD = 4,
		BEST = 5
	};

	if(rar->file.service > 0) {
		return do_unstore_file(a, rar, buf, size, offset);
	} else {
		switch(rar->cstate.method) {
			case STORE:
				return do_unstore_file(a, rar, buf, size,
				    offset);
			case FASTEST:
				/* fallthrough */
			case FAST:
				/* fallthrough */
			case NORMAL:
				/* fallthrough */
			case GOOD:
				/* fallthrough */
			case BEST:
				return uncompress_file(a);
			default:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Compression method not supported: 0x%x",
				    rar->cstate.method);

				return ARCHIVE_FATAL;
		}
	}

#if !defined WIN32
	/* Not reached. */
	return ARCHIVE_OK;
#endif
}