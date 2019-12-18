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
struct TYPE_2__ {scalar_t__ endarc; } ;
struct rar5 {int header_initialized; int skipped_magic; TYPE_1__ main; } ;
struct archive_read {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_RETRY ; 
 int consume (struct archive_read*,int /*<<< orphan*/ ) ; 
 struct rar5* get_context (struct archive_read*) ; 
 int /*<<< orphan*/  init_header (struct archive_read*) ; 
 int process_base_block (struct archive_read*,struct archive_entry*) ; 
 int /*<<< orphan*/  rar5_signature_size ; 

__attribute__((used)) static int rar5_read_header(struct archive_read *a,
    struct archive_entry *entry)
{
	struct rar5* rar = get_context(a);
	int ret;

	if(rar->header_initialized == 0) {
		init_header(a);
		rar->header_initialized = 1;
	}

	if(rar->skipped_magic == 0) {
		if(ARCHIVE_OK != consume(a, rar5_signature_size)) {
			return ARCHIVE_EOF;
		}

		rar->skipped_magic = 1;
	}

	do {
		ret = process_base_block(a, entry);
	} while(ret == ARCHIVE_RETRY ||
			(rar->main.endarc > 0 && ret == ARCHIVE_OK));

	return ret;
}