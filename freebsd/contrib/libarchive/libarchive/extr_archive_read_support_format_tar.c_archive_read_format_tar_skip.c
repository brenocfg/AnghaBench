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
struct tar {scalar_t__ entry_bytes_remaining; scalar_t__ entry_padding; scalar_t__ entry_bytes_unconsumed; struct sparse_block* sparse_list; } ;
struct sparse_block {scalar_t__ remaining; int /*<<< orphan*/  hole; struct sparse_block* next; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int /*<<< orphan*/  gnu_clear_sparse_list (struct tar*) ; 

__attribute__((used)) static int
archive_read_format_tar_skip(struct archive_read *a)
{
	int64_t bytes_skipped;
	int64_t request;
	struct sparse_block *p;
	struct tar* tar;

	tar = (struct tar *)(a->format->data);

	/* Do not consume the hole of a sparse file. */
	request = 0;
	for (p = tar->sparse_list; p != NULL; p = p->next) {
		if (!p->hole) {
			if (p->remaining >= INT64_MAX - request) {
				return ARCHIVE_FATAL;
			}
			request += p->remaining;
		}
	}
	if (request > tar->entry_bytes_remaining)
		request = tar->entry_bytes_remaining;
	request += tar->entry_padding + tar->entry_bytes_unconsumed;

	bytes_skipped = __archive_read_consume(a, request);
	if (bytes_skipped < 0)
		return (ARCHIVE_FATAL);

	tar->entry_bytes_remaining = 0;
	tar->entry_bytes_unconsumed = 0;
	tar->entry_padding = 0;

	/* Free the sparse list. */
	gnu_clear_sparse_list(tar);

	return (ARCHIVE_OK);
}