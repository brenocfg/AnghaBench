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
typedef  int uint64_t ;
struct rar5 {int qlist_offset; int rr_offset; } ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  read_var (struct archive_read*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_main_locator_extra_block(struct archive_read* a,
    struct rar5* rar)
{
	uint64_t locator_flags;

	if(!read_var(a, &locator_flags, NULL)) {
		return ARCHIVE_EOF;
	}

	enum LOCATOR_FLAGS {
		QLIST = 0x01, RECOVERY = 0x02,
	};

	if(locator_flags & QLIST) {
		if(!read_var(a, &rar->qlist_offset, NULL)) {
			return ARCHIVE_EOF;
		}

		/* qlist is not used */
	}

	if(locator_flags & RECOVERY) {
		if(!read_var(a, &rar->rr_offset, NULL)) {
			return ARCHIVE_EOF;
		}

		/* rr is not used */
	}

	return ARCHIVE_OK;
}