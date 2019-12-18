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
struct id_array {int count; int size; scalar_t__* ids; } ;
struct archive_match {int /*<<< orphan*/  setflag; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ID_IS_SET ; 
 int error_nomem (struct archive_match*) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,unsigned int) ; 
 void* realloc (scalar_t__*,int) ; 

__attribute__((used)) static int
add_owner_id(struct archive_match *a, struct id_array *ids, int64_t id)
{
	unsigned i;

	if (ids->count + 1 >= ids->size) {
		void *p;

		if (ids->size == 0)
			ids->size = 8;
		else
			ids->size *= 2;
		p = realloc(ids->ids, sizeof(*ids->ids) * ids->size);
		if (p == NULL)
			return (error_nomem(a));
		ids->ids = (int64_t *)p;
	}

	/* Find an insert point. */
	for (i = 0; i < ids->count; i++) {
		if (ids->ids[i] >= id)
			break;
	}

	/* Add owner id. */
	if (i == ids->count)
		ids->ids[ids->count++] = id;
	else if (ids->ids[i] != id) {
		memmove(&(ids->ids[i+1]), &(ids->ids[i]),
		    (ids->count - i) * sizeof(ids->ids[0]));
		ids->ids[i] = id;
		ids->count++;
	}
	a->setflag |= ID_IS_SET;
	return (ARCHIVE_OK);
}