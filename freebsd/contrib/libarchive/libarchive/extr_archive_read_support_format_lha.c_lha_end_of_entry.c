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
struct lha {int end_of_entry_cleanup; int setflag; scalar_t__ crc; scalar_t__ entry_crc_calculated; } ;
struct archive_read {int /*<<< orphan*/  archive; TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_WARN ; 
 int CRC_IS_SET ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
lha_end_of_entry(struct archive_read *a)
{
	struct lha *lha = (struct lha *)(a->format->data);
	int r = ARCHIVE_EOF;

	if (!lha->end_of_entry_cleanup) {
		if ((lha->setflag & CRC_IS_SET) &&
		    lha->crc != lha->entry_crc_calculated) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "LHa data CRC error");
			r = ARCHIVE_WARN;
		}

		/* End-of-entry cleanup done. */
		lha->end_of_entry_cleanup = 1;
	}
	return (r);
}