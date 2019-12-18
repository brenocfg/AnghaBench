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
struct TYPE_2__ {int last_header_id; scalar_t__ split_before; } ;
struct rar5 {TYPE_1__ generic; } ;
struct archive_read {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_RETRY ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 struct rar5* get_context (struct archive_read*) ; 
 int process_base_block (struct archive_read*,struct archive_entry*) ; 

__attribute__((used)) static int skip_base_block(struct archive_read* a) {
	int ret;
	struct rar5* rar = get_context(a);

	/* Create a new local archive_entry structure that will be operated on
	 * by header reader; operations on this archive_entry will be discarded.
	 */
	struct archive_entry* entry = archive_entry_new();
	ret = process_base_block(a, entry);

	/* Discard operations on this archive_entry structure. */
	archive_entry_free(entry);
	if(ret == ARCHIVE_FATAL)
		return ret;

	if(rar->generic.last_header_id == 2 && rar->generic.split_before > 0)
		return ARCHIVE_OK;

	if(ret == ARCHIVE_OK)
		return ARCHIVE_RETRY;
	else
		return ret;
}