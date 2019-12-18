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
struct TYPE_2__ {int service; } ;
struct rar5 {TYPE_1__ file; } ;
struct archive_read {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_RETRY ; 
 int process_head_file (struct archive_read*,struct rar5*,struct archive_entry*,size_t) ; 
 int rar5_read_data_skip (struct archive_read*) ; 

__attribute__((used)) static int process_head_service(struct archive_read* a, struct rar5* rar,
    struct archive_entry* entry, size_t block_flags)
{
	/* Process this SERVICE block the same way as FILE blocks. */
	int ret = process_head_file(a, rar, entry, block_flags);
	if(ret != ARCHIVE_OK)
		return ret;

	rar->file.service = 1;

	/* But skip the data part automatically. It's no use for the user
	 * anyway.  It contains only service data, not even needed to
	 * properly unpack the file. */
	ret = rar5_read_data_skip(a);
	if(ret != ARCHIVE_OK)
		return ret;

	/* After skipping, try parsing another block automatically. */
	return ARCHIVE_RETRY;
}