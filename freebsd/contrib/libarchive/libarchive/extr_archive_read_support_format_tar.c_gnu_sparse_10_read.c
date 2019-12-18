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
struct tar {scalar_t__ entry_bytes_remaining; } ;
struct archive_read {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ __archive_read_consume (struct archive_read*,scalar_t__) ; 
 scalar_t__ gnu_add_sparse_entry (struct archive_read*,struct tar*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gnu_clear_sparse_list (struct tar*) ; 
 scalar_t__ gnu_sparse_10_atol (struct archive_read*,struct tar*,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  tar_flush_unconsumed (struct archive_read*,size_t*) ; 

__attribute__((used)) static ssize_t
gnu_sparse_10_read(struct archive_read *a, struct tar *tar, size_t *unconsumed)
{
	ssize_t bytes_read;
	int entries;
	int64_t offset, size, to_skip, remaining;

	/* Clear out the existing sparse list. */
	gnu_clear_sparse_list(tar);

	remaining = tar->entry_bytes_remaining;

	/* Parse entries. */
	entries = (int)gnu_sparse_10_atol(a, tar, &remaining, unconsumed);
	if (entries < 0)
		return (ARCHIVE_FATAL);
	/* Parse the individual entries. */
	while (entries-- > 0) {
		/* Parse offset/size */
		offset = gnu_sparse_10_atol(a, tar, &remaining, unconsumed);
		if (offset < 0)
			return (ARCHIVE_FATAL);
		size = gnu_sparse_10_atol(a, tar, &remaining, unconsumed);
		if (size < 0)
			return (ARCHIVE_FATAL);
		/* Add a new sparse entry. */
		if (gnu_add_sparse_entry(a, tar, offset, size) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}
	/* Skip rest of block... */
	tar_flush_unconsumed(a, unconsumed);
	bytes_read = (ssize_t)(tar->entry_bytes_remaining - remaining);
	to_skip = 0x1ff & -bytes_read;
	/* Fail if tar->entry_bytes_remaing would get negative */
	if (to_skip > remaining)
		return (ARCHIVE_FATAL);
	if (to_skip != __archive_read_consume(a, to_skip))
		return (ARCHIVE_FATAL);
	return ((ssize_t)(bytes_read + to_skip));
}