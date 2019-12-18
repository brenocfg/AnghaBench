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
struct TYPE_2__ {scalar_t__ bytes_remaining; } ;
struct rar5 {TYPE_1__ file; scalar_t__ merge_mode; } ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int consume (struct archive_read*,scalar_t__) ; 
 struct rar5* get_context (struct archive_read*) ; 
 int rar5_read_data_skip (struct archive_read*) ; 

__attribute__((used)) static int skip_unprocessed_bytes(struct archive_read* a) {
	struct rar5* rar = get_context(a);
	int ret;

	if(rar->file.bytes_remaining) {
		/* Use different skipping method in block merging mode than in
		 * normal mode. If merge mode is active, rar5_read_data_skip
		 * can't be used, because it could allow recursive use of
		 * merge_block() * function, and this function doesn't support
		 * recursive use. */
		if(rar->merge_mode) {
			/* Discard whole merged block. This is valid in solid
			 * mode as well, because the code will discard blocks
			 * only if those blocks are safe to discard (i.e.
			 * they're not FILE blocks).  */
			ret = consume(a, rar->file.bytes_remaining);
			if(ret != ARCHIVE_OK) {
				return ret;
			}
			rar->file.bytes_remaining = 0;
		} else {
			/* If we're not in merge mode, use safe skipping code.
			 * This will ensure we'll handle solid archives
			 * properly. */
			ret = rar5_read_data_skip(a);
			if(ret != ARCHIVE_OK) {
				return ret;
			}
		}
	}

	return ARCHIVE_OK;
}