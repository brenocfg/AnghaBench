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
struct archive_entry {struct ae_sparse* sparse_tail; struct ae_sparse* sparse_head; } ;
struct ae_sparse {scalar_t__ offset; scalar_t__ length; struct ae_sparse* next; } ;
typedef  scalar_t__ la_int64_t ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 scalar_t__ malloc (int) ; 

void
archive_entry_sparse_add_entry(struct archive_entry *entry,
	la_int64_t offset, la_int64_t length)
{
	struct ae_sparse *sp;

	if (offset < 0 || length < 0)
		/* Invalid value */
		return;
	if (offset > INT64_MAX - length ||
	    offset + length > archive_entry_size(entry))
		/* A value of "length" parameter is too large. */
		return;
	if ((sp = entry->sparse_tail) != NULL) {
		if (sp->offset + sp->length > offset)
			/* Invalid value. */
			return;
		if (sp->offset + sp->length == offset) {
			if (sp->offset + sp->length + length < 0)
				/* A value of "length" parameter is
				 * too large. */
				return;
			/* Expand existing sparse block size. */
			sp->length += length;
			return;
		}
	}

	if ((sp = (struct ae_sparse *)malloc(sizeof(*sp))) == NULL)
		/* XXX Error XXX */
		return;

	sp->offset = offset;
	sp->length = length;
	sp->next = NULL;

	if (entry->sparse_head == NULL)
		entry->sparse_head = entry->sparse_tail = sp;
	else {
		/* Add a new sparse block to the tail of list. */
		if (entry->sparse_tail != NULL)
			entry->sparse_tail->next = sp;
		entry->sparse_tail = sp;
	}
}