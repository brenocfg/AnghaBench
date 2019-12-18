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
struct tar {int /*<<< orphan*/ * sparse_last; struct sparse_block* sparse_list; } ;
struct sparse_block {struct sparse_block* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sparse_block*) ; 

__attribute__((used)) static void
gnu_clear_sparse_list(struct tar *tar)
{
	struct sparse_block *p;

	while (tar->sparse_list != NULL) {
		p = tar->sparse_list;
		tar->sparse_list = p->next;
		free(p);
	}
	tar->sparse_last = NULL;
}