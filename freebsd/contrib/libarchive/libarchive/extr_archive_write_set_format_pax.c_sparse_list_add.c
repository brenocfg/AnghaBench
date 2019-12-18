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
struct pax {TYPE_1__* sparse_tail; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ remaining; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int _sparse_list_add_block (struct pax*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int
sparse_list_add(struct pax *pax, int64_t offset, int64_t length)
{
	int64_t last_offset;
	int r;

	if (pax->sparse_tail == NULL)
		last_offset = 0;
	else {
		last_offset = pax->sparse_tail->offset +
		    pax->sparse_tail->remaining;
	}
	if (last_offset < offset) {
		/* Add a hole block. */
		r = _sparse_list_add_block(pax, last_offset,
		    offset - last_offset, 1);
		if (r != ARCHIVE_OK)
			return (r);
	}
	/* Add data block. */
	return (_sparse_list_add_block(pax, offset, length, 0));
}