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
struct TYPE_2__ {struct extr_rec* current; struct extr_rec** last; struct extr_rec* first; } ;
struct isoent {TYPE_1__ extr_rec_list; struct isoent* parent; } ;
struct extr_rec {int offset; int location; unsigned char* buf; struct extr_rec* next; } ;

/* Variables and functions */
 scalar_t__ DR_SAFETY ; 
 scalar_t__ LOGICAL_BLOCK_SIZE ; 
 struct extr_rec* extra_last_record (struct isoent*) ; 
 struct extr_rec* malloc (int) ; 

__attribute__((used)) static unsigned char *
extra_get_record(struct isoent *isoent, int *space, int *off, int *loc)
{
	struct extr_rec *rec;

	isoent = isoent->parent;
	if (off != NULL) {
		/* Storing data into an extra record. */
		rec = isoent->extr_rec_list.current;
		if (DR_SAFETY > LOGICAL_BLOCK_SIZE - rec->offset)
			rec = rec->next;
	} else {
		/* Calculating the size of an extra record. */
		rec = extra_last_record(isoent);
		if (rec == NULL ||
		    DR_SAFETY > LOGICAL_BLOCK_SIZE - rec->offset) {
			rec = malloc(sizeof(*rec));
			if (rec == NULL)
				return (NULL);
			rec->location = 0;
			rec->offset = 0;
			/* Insert `rec` into the tail of isoent->extr_rec_list */
			rec->next = NULL;
			/*
			 * Note: testing isoent->extr_rec_list.last == NULL
			 * here is really unneeded since it has been already
			 * initialized at isoent_new function but Clang Static
			 * Analyzer claims that it is dereference of null
			 * pointer.
			 */
			if (isoent->extr_rec_list.last == NULL)
				isoent->extr_rec_list.last =
					&(isoent->extr_rec_list.first);
			*isoent->extr_rec_list.last = rec;
			isoent->extr_rec_list.last = &(rec->next);
		}
	}
	*space = LOGICAL_BLOCK_SIZE - rec->offset - DR_SAFETY;
	if (*space & 0x01)
		*space -= 1;/* Keep padding space. */
	if (off != NULL)
		*off = rec->offset;
	if (loc != NULL)
		*loc = rec->location;
	isoent->extr_rec_list.current = rec;

	return (&rec->buf[rec->offset]);
}