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
struct sparse_block {int is_hole; struct sparse_block* next; void* remaining; void* offset; } ;
struct pax {struct sparse_block* sparse_tail; struct sparse_block* sparse_list; } ;
typedef  void* int64_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static int
_sparse_list_add_block(struct pax *pax, int64_t offset, int64_t length,
    int is_hole)
{
	struct sparse_block *sb;

	sb = (struct sparse_block *)malloc(sizeof(*sb));
	if (sb == NULL)
		return (ARCHIVE_FATAL);
	sb->next = NULL;
	sb->is_hole = is_hole;
	sb->offset = offset;
	sb->remaining = length;
	if (pax->sparse_list == NULL || pax->sparse_tail == NULL)
		pax->sparse_list = pax->sparse_tail = sb;
	else {
		pax->sparse_tail->next = sb;
		pax->sparse_tail = sb;
	}
	return (ARCHIVE_OK);
}